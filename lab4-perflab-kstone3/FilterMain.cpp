#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

class Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}


double
applyFilter(class Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  output -> width = input -> width;
  output -> height = input -> height;

    //Calcualting outside for loops so it doesn't have to do it multiple times
    int width = input->width-1;
    int height = input->height-1;
    int divisor = filter->getDivisor();
    int result = 0;
    int filter0 = filter -> get(0,0);
    int filter1 = filter -> get(0,1);
    int filter2 = filter -> get(0,2);
    int filter3 = filter -> get(1,0);
    int filter4 = filter -> get(1,1);
    int filter5 = filter -> get(1,2);
    int filter6 = filter -> get(2,0);
    int filter7 = filter -> get(2,1);
    int filter8 = filter -> get(2,2);
    //reagranged loops to be in row major order and unrolled them 4 times
for(int plane = 0; plane < 3; plane++) {
    for(int row = 1; row < (height) ; row++) {
      for(int col = 1; col < (width) ; col++) {
 

          
output -> color[plane][row][col] = 0;

// 	for (int j = 0; j < filtersize; j+=3) {
// 	  for (int i = 0; i < filtersize; i+=3) {	
        result = (input -> color[plane][row  - 1][col -1] * filter0 );
        result = result  + (input -> color[plane][row - 1][col ] * filter1);
        result = result  + (input -> color[plane][row - 1][col +1] * filter2 );
        result = result  + (input -> color[plane][row ][col -1] * filter3 );
        result = result  + (input -> color[plane][row ][col ] * filter4 );
        result = result  + (input -> color[plane][row ][col +1] * filter5);
        result = result  + (input -> color[plane][row +1][col -1] * filter6 );
        result = result  + (input -> color[plane][row +1][col ] * filter7 );
        result = result  + (input -> color[plane][row +1][col +1] * filter8);
          //val4= val4 + (input -> color[plane][row + i +2][col + j +2]  * filter -> get(i+3, j+3) );
// 	  }
// 	}
	output -> color[plane][row][col] = result;
	output -> color[plane][row][col] = 	output -> color[plane][row][col] / divisor;

	if ( output -> color[plane][row][col]  < 0 ) {
	  output -> color[plane][row][col] = 0;
	}

	if ( output -> color[plane][row][col]  > 255 ) { 
	  output -> color[plane][row][col] = 255;
	}
    
          
          
// 	val2 = val2/divisor;

// 	if ( val2  < 0 ) {
// 	  val2 = 0;
// 	}

// 	if ( val2  > 255 ) { 
// 	  val2 = 255;
// 	}
//           output -> color[plane][row+1][col+1] = val2;
          
          
// 	val3 = val3/divisor;

// 	if ( val3  < 0 ) {
// 	  val3 = 0;
// 	}

// 	if ( val3  > 255 ) { 
// 	  val3 = 255;
// 	}
//           output -> color[plane][row+2][col+2] = val3;
          
          
// 	val4 = val4/divisor;

// 	if ( val4  < 0 ) {
// 	  val4 = 0;
// 	}

// 	if ( val4  > 255 ) { 
// 	  val4 = 255;
// 	}
//           output -> color[plane][row+3][col+3] = val4;
      }
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
