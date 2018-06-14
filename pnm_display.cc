#include "pnm_display.h"
#include "iostream"
#include "fstream"
#include <string>

int frame_num = 0;

int pnm_init_display(void){
	ppm_buf = new float*[display_xSize];
	for(int i = 0; i < display_xSize; i++){
		ppm_buf[i] = new float[display_ySize * 3];
	}
	return RD_OK;
}

int pnm_end_display(void){
	//std::cerr << "hello?\n";
	for(int i = 0; i < display_xSize; i++){
		delete[] ppm_buf[i];
	}
	delete[] ppm_buf;
	return RD_OK;
}

int pnm_init_frame(int fr_num){
	pnm_clear();
	frame_num = fr_num;
	return RD_OK;
}

int pnm_end_frame(void){
	std::string fname = display_name + std::to_string(frame_num) + ".ppm";
	std::ofstream ppm_out(fname, std::ios::out | std::ios::trunc);
	ppm_out << "P3\n";
	ppm_out << std::to_string(display_xSize) << ' ' << std::to_string(display_ySize) << '\n';
	ppm_out << "256\n";
	unsigned char red, green, blue;
	for(int j = 0; j < display_ySize; j++){
		for(int i = 0; i < display_xSize; i++){
			red = (unsigned char) ((ppm_buf[i][3 * j] * 255) + 0.5);
			green = (unsigned char) ((ppm_buf[i][3 * j + 1] * 255) + 0.5);
			blue = (unsigned char) ((ppm_buf[i][3 * j + 2] * 255) + 0.5);
			ppm_out << std::to_string(red) << ' ' <<std::to_string(green) << ' ' << std::to_string(blue) << '\n';
		}
	}
	ppm_out.close();
	return RD_OK;
}

int pnm_write_pixel(int x, int y, const float rgb []){
	if(x >= 0 && y >= 0 && x < display_xSize && y < display_ySize){
		ppm_buf[x][3 * y]   = rgb[0];
		ppm_buf[x][3 * y+1] = rgb[1];
		ppm_buf[x][3 * y+2] = rgb[2];
	}
	return RD_OK;
}

int pnm_read_pixel(int x, int y, float rgb []){
	if(x >= 0 && y >= 0 && x < display_xSize && y < display_ySize){
		rgb[0] = ppm_buf[x][3 * y];
		rgb[1] = ppm_buf[x][3 * y + 1];
		rgb[2] = ppm_buf[x][3 * y + 2];
	}
	else{
		rgb[0] = bg_color[0];
		rgb[1] = bg_color[1];
		rgb[2] = bg_color[2];
	}
	return RD_OK;
}

int pnm_set_background(const float rgb []){
	bg_color[0] = rgb[0];
	bg_color[1] = rgb[1];
	bg_color[2] = rgb[2];
	//pnm_clear();
	return RD_OK;
}

int pnm_clear(){
	for(int j = 0; j < display_ySize; j++){
		for(int i = 0; i < display_xSize; i++){
			ppm_buf[i][3 * j] = bg_color[0];
			ppm_buf[i][3 * j + 1] = bg_color[1];
			ppm_buf[i][3 * j + 2] = bg_color[2];
		}
	}
	return RD_OK;
}
