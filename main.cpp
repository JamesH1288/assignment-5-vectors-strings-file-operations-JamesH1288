#include "pixel.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

std::vector<Pixel> pixel_list;

//height and width variables for the swap method
int width = 0;
int height = 0;

Pixel make_pixel(const std::string& line){

	Pixel pixel;
	int pos =0;
	int next = line.find(',');

	//substring to capture pixel data, x, y and rgb
	pixel.x = std::stoi(line.substr(pos, next-pos));
	pos = next +1;

	next = line.find(',', pos);
	pixel.y = std::stoi(line.substr(pos, next-pos));
	pos = next +1;

	next = line.find(',', pos);
	pixel.r = std::stof(line.substr(pos, next-pos));
	pos = next +1;

	next = line.find(',', pos);
	pixel.g = std::stof(line.substr(pos, next-pos));
	pos = next+1;

	pixel.b = std::stof(line.substr(pos));

	return pixel;
		
}

void average_colors(
	const std::vector<Pixel>& pixel_list,
	double& avgR, double& avgG, double& avgB
						){

	double rSum = 0.0;
	double gSum = 0.0;
	double bSum = 0.0;

	int count = pixel_list.size();

	//loop through and sums r, g, b pixels
	for (int i = 0; i < count; i++){
		rSum += pixel_list[i].r;
		gSum += pixel_list[i].g;
		bSum += pixel_list[i].b;
	}
	
	avgR = rSum/count;
	avgG = gSum/count;
	avgB = bSum/count;

}


void flip_vertically(std::vector<Pixel> &pixel_list){

	//loops through pixel_list height, swaps maxIndex and bottomIndex
	for(int row =0; row < height /2; ++row){
		for (int col = 0; col < width; ++col){
			int maxIndex = row*width + col;
			int bottomIndex = (height-row-1) * width + col;
			std::swap(pixel_list[maxIndex], pixel_list[bottomIndex]);
		}
	}

}

int main(int argc, char* argv[]){
	
	
	std::ifstream infile(argv[1]);
	std::string line;

	while (std::getline(infile, line)){
		if (line.empty()) continue; // checks for empty lines
		Pixel p = make_pixel(line);
		pixel_list.push_back(p);
	}
	infile.close();

	int max_y = 0;
	
	//calling flip_vertically function
	flip_vertically(pixel_list);
	double avgR, avgG, avgB;
	average_colors(pixel_list, avgR, avgG, avgB);
	
	//output file name
	std::ofstream outfile("flipped.dat");
	
	for (int i =0; i <pixel_list.size(); i++){
		outfile << pixel_list[i].x << "," << pixel_list[i].y << "," 
		<< pixel_list[i].r << "," << pixel_list[i].g << "," 
		<< pixel_list[i].b << "\n";

	}
		
	//old code below
	/*Pixel *p = (Pixel *)malloc(sizeof(Pixel));
	p->r = 0.5;
	p->g = 0.5;
	p->b = 0.5;
	pixel_list.push_back(p);
	std::cout << pixel_list[0]->r<<"\t"<<
	pixel_list[0]->g<<"\t"<<pixel_list[0]->b<<
	std::endl; */
	return 0;
}

