#ifndef HISTOGRAM1D_H
#define HISTOGRAM1D_H

#include <vector>
#include <cstring>
#include <cstdlib>
#include <fstream>

struct histogram1d: std::vector<double> {
  std::string name;
  double start;
  double step;
  double last;
  histogram1d(double min_data, double max_data, double bin_width);
  void CreateFromFile(std::ifstream& histfile);
  int Bin(double data);
  void Update(double data);
  void Clear();
};

inline histogram1d::histogram1d(double min_data, double max_data, double bin_width){
	start = min_data;
	step = bin_width;
	last = max_data;

  double size = (max_data - min_data)/bin_width ;
	int hist_size = int(size) + 1 ;

	for(int i = 0; i < hist_size; i++){
		push_back(0);
	}
}

inline void histogram1d::CreateFromFile(std::ifstream& histfile){
	char line[60];
	char *bin;
	char *value;
	/* read first line and set start */
	histfile.getline(line,60);
	bin  = strtok(line, " \n\t");
	value = strtok(NULL, " \n\t");
	start = atoi(bin);
	push_back(atoi(value));
	/* read second line and set step */
	histfile.getline(line,60);
	bin  = strtok(line, " \n\t");
	value = strtok(NULL, " \n\t");
	step = atof(bin)-start;
	push_back(atoi(value));
	/* read other lines */
	while (histfile.getline(line,60)) {
		bin  = strtok(line, " \n\t");
		value = strtok(NULL, " \n\t");
		push_back(atoi(value));
	}	
}

inline int histogram1d::Bin(double data){
  int bin;
	if (data < start) bin = 0;
  else if (data >= last) bin = int( (last-start)/step + 0.5);
	else bin = int( (data-start)/step + 0.5 );
  return bin;
}

inline void histogram1d::Update(double data){
	(*this)[ Bin(data) ]++;
}

inline void histogram1d::Clear(){
	for (int i = 0; i < (*this).size(); i++){
		(*this)[i]=0;
	}
}

std::ostream& operator<< (std::ostream& out, const histogram1d& hist ) {
	double data = hist.start;
	for(std::vector<double>::const_iterator bin = hist.begin(); bin < hist.end(); ++bin){
		out<<data<<"\t"<<(*bin)<<std::endl;
		data+=hist.step;
	}
	return out;
}

#endif

