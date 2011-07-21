#ifndef HISTOGRAM2D_H
#define HISTOGRAM2D_H

#include <vector>
#include <cstring>

struct histogram2d : std::vector< std::vector<double> >{
  std::string title;
  std::string x_label;
  std::string y_label;

  double x_start;
  double x_last;
  double x_step;

  double y_start;
  double y_last;
  double y_step;

  histogram2d(double min_x_data,double max_x_data, 
              double min_y_data, double max_y_data, 
              double bin_x_width, double bin_y_width);
  void CreateFromFile(std::ifstream& histfile); //TODO
  int BinX(double x_data);
  int BinY(double y_data);
  void Update(double x_data, double y_data);
  void Clear();
};

inline histogram2d::histogram2d(double min_x_data,double max_x_data, 
												 double min_y_data, double max_y_data, 
												 double bin_x_width, double bin_y_width){
	x_start = min_x_data;
	y_start = min_y_data;
	x_step = bin_x_width;
	y_step = bin_y_width;
	x_last = max_x_data;
	y_last = max_y_data;

  double x_size = (max_x_data-min_x_data)/bin_x_width;
	int xsize = int( x_size ) + 1;
  double y_size = (max_y_data-min_y_data)/bin_y_width;
	int ysize = int( y_size ) + 1;

	for(int i = 0; i < xsize; i++){
		std::vector<double> col;
		for (int j = 0; j < ysize; j++){
			col.push_back(0);
		}
		push_back(col);
	}
}

inline int histogram2d::BinX(double x_data){
  int binx;
	if (x_data < x_start) binx = 0;
	else if (x_data > x_last) binx = int( (x_last-x_start)/x_step + 0.5);
	else binx = int( (x_data-x_start)/x_step + 0.5 );
  return binx;
}

inline int histogram2d::BinY(double y_data){
  int biny;
	if (y_data < y_start) biny = 0;
	else if (y_data > y_last) biny = int( (y_last-y_start)/y_step + 0.5);
	else biny = int( (y_data-y_start)/y_step + 0.5 );
  return biny;
}

inline void histogram2d::Update(double x_data, double y_data){
	(*this)[ BinX(x_data) ][ BinY(y_data) ]++;
}

inline void histogram2d::Clear(){
	for(int i = 0; i < this->size(); i++){
		for (int j = 0; j < (*this)[0].size(); j++){
			(*this)[i][j]=0;
		}
	}
}

std::ostream& operator<< (std::ostream& out, const histogram2d& hist ) {
	out << hist.title << std::endl;
	out << hist.x_start << "\t" << hist.x_last << "\t" << hist.x_step << "\t" << hist.size() << "\t" << hist.x_label << std::endl;
	out << hist.y_start << "\t" << hist.y_last << "\t" << hist.y_step << "\t" << hist[0].size() << "\t" << hist.y_label << std::endl;

	double x_data = hist.x_start;
	for(std::vector< std::vector<double> >::const_iterator xbin = hist.begin(); xbin < hist.end(); ++xbin){
		double y_data = hist.y_start;
		for(std::vector<double>::const_iterator ybin = xbin->begin(); ybin < xbin->end(); ++ybin){
			if ( (*ybin)!=0 ) out << x_data << "\t" << y_data << "\t" << (*ybin) << std::endl;
			y_data += hist.y_step;
		}
		x_data += hist.x_step;
	}

	return out;
}

#endif
