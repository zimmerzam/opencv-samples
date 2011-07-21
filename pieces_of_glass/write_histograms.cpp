#include <algorithm>
#include <cmath>
#include "routines/histogram1d.h"
#include "routines/histogram2d.h"

int main(int argc, char* argv[]){
	char line[256];
  char* index;
	char* area;
	char* length;
	char* minSize;
	char* maxSize;
	char* edges;
	char* bar_x;
	char* bar_y;
	histogram1d hist_area(0,90000,1);
	histogram1d hist_length(0,3000,1);
	histogram1d hist_min(0,3000,1);
	histogram1d hist_max(0,3000,1);
	histogram1d hist_edges(0,50,1);
	histogram2d hist_bar(0, 10000, 0, 10000, 1, 1);
	for (int i = 1; i < argc; i++){
		std::ifstream file( argv[i] );
		while( file.getline(line, 256) ){
			index = strtok(line, " \t\n");
			area = strtok(NULL, " \t\n");
			length = strtok(NULL, " \t\n");
			minSize = strtok(NULL, " \t\n");
			maxSize = strtok(NULL, " \t\n");
			edges = strtok(NULL, " \t\n");
			bar_x = strtok(NULL, " \t\n");
			bar_y = strtok(NULL, " \t\n");

			hist_area.Update( (atof(area)) );
			hist_length.Update( (atof(length)) );
			hist_min.Update( (atof(minSize)) );
			hist_max.Update( (atof(maxSize)) );
			hist_edges.Update( (atof(edges)) );
			hist_bar.Update( atof(bar_x), atof(bar_y) );
		}
		file.close();
	}
	std::ofstream area_out("area_hist.dat");
	area_out << hist_area;
	std::ofstream length_out("length_hist.dat");
	length_out << hist_length;
	std::ofstream min_out("minSize_hist.dat");
	min_out << hist_min;
	std::ofstream max_out("maxSize_hist.dat");
	max_out << hist_max;
	std::ofstream edges_out("edges_hist.dat");
	edges_out << hist_edges;

	std::ofstream bar_out("barycenter_hist.dat");
	bar_out << hist_bar;

	return 0;
}

