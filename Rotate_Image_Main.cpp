#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

# define org_row  512 
# define org_col  512
# define sizebyte 1

# define FALSE 0
# define TRUE 1
# define in_file_name "lena"
# define right90_out_file_name "_right90"
# define right180_out_file_name "_right180"
# define left90_out_file_name "_left90"
# define Hor_mirror_out_file_name "_Hor_mirror"
# define Ver_mirror_out_file_name "_Ver_mirror"

using namespace std;


//unsigned char 형파일 읽기
unsigned char* readFile(const char* s, int size_row, int size_col) {
	//FILE* input_img = fopen(in_file, "rb");
	FILE* input_img;
	fopen_s(&input_img, s, "rb");
	unsigned char* org_img = NULL;
	org_img = (unsigned char*)malloc(sizeof(unsigned char)*(size_row*size_col));
	if (input_img == NULL) {
		puts("input 파일 오픈 실패 ");
		return NULL;
	}
	else {
		fseek(input_img, 0, SEEK_SET);
		fread((void*)org_img, sizebyte, size_row * size_col, input_img);
	}
	return org_img;
	fclose(input_img);
	free(org_img);
}

//unsigned char 형 파일 쓰기
unsigned char* WriteFile_U(unsigned char* out_img, const char* s, int size_row, int size_col) {
	//FILE* output_img = fopen(out_file, "wb");
	FILE* output_img;
	fopen_s(&output_img, s, "wb");
	if (output_img == NULL) {
		puts("output 파일 오픈 실패");
		return NULL;
	}
	else {
		fseek(output_img, 0, SEEK_SET);
		fwrite((void*)out_img, sizebyte, size_row*size_col, output_img);
	}
	fclose(output_img);
	return out_img;

}

//오른쪽으로 90도 회전
unsigned char* make_right90(unsigned char* org_img, int size_row, int size_col) {
	unsigned char* right90_output_img = (unsigned char*)malloc(sizeof(unsigned char)*(org_row*org_col));
	int i, j;
	for (i = 0; i < size_row; i++)
	{
		for (j = 0; j < size_col; j++) {
			*(right90_output_img + i * size_row + j) = *(org_img + ((size_row-1) - j) * size_col + i);
		}
	}
	return right90_output_img;
}

//오른쪽으로 180도 회전
unsigned char* make_right180(unsigned char* org_img, int size_row, int size_col) {
	unsigned char* right180_output_img = (unsigned char*)malloc(sizeof(unsigned char)*(size_row*size_col));
	int i, j;
	for (i = 0; i < size_row; i++)
	{
		for (j = 0; j < size_col; j++) {
			*(right180_output_img + i * size_col + j) = *(org_img + ((size_row-1) - i) * size_col + ((size_col-1) - j));
		}
	}
	return right180_output_img;
}

//왼쪽으로 90도 회전
unsigned char* make_left90(unsigned char* org_img, int size_row, int size_col) {
	unsigned char* left90_output_img = (unsigned char*)malloc(sizeof(unsigned char)*(size_row*size_col));
	int i, j;
	for (i = 0; i < size_row; i++)
	{
		for (j = 0; j < size_col; j++) {
			*(left90_output_img + i * size_col + j) = *(org_img + j * size_col + ((size_col-1) - i));
		}
	}
	return left90_output_img;
}

//수평 반전
unsigned char* make_Hor_mirror(unsigned char* org_img, int size_row, int size_col) {
	unsigned char* Hor_mirror_output_img = (unsigned char*)malloc(sizeof(unsigned char)*(size_row*size_col));
	int i, j;
	for (i = 0; i < size_row; i++)
	{
		for (j = 0; j < size_col; j++) {
			*(Hor_mirror_output_img + i * size_col + j) = *(org_img + i * size_col + ((size_col-1) - j));
		}
	}
	return Hor_mirror_output_img;
}

//수직반전
unsigned char* make_Ver_mirror(unsigned char* org_img, int size_row, int size_col) {
	unsigned char* Ver_mirror_output_img = (unsigned char*)malloc(sizeof(unsigned char)*(size_row*size_col));
	int i, j;
	for (i = 0; i < size_row; i++)
	{
		for (j = 0; j < size_col; j++) {
			*(Ver_mirror_output_img + i * size_col + j) = *(org_img + ((size_row-1) - i) * size_col + j);
		}
	}
	return Ver_mirror_output_img;
}


//main 함수
int main() {
	//인수 선언
	unsigned char* input_img = (unsigned char*)malloc(sizeof(unsigned char)*(org_row*org_col));
	unsigned char* right90_output_img = (unsigned char*)malloc(sizeof(unsigned char)*(org_row*org_col));
	unsigned char* right180_output_img = (unsigned char*)malloc(sizeof(unsigned char)*(org_row*org_col));
	unsigned char* left90_output_img = (unsigned char*)malloc(sizeof(unsigned char)*(org_row*org_col));
	unsigned char* Hor_mirror_output_img = (unsigned char*)malloc(sizeof(unsigned char)*(org_row*org_col));
	unsigned char* Ver_mirror_output_img = (unsigned char*)malloc(sizeof(unsigned char)*(org_row*org_col));

	//원본 파일 입력
	const char* input_file = in_file_name".img";
	input_img = readFile(input_file , org_row, org_col);

	//영상 변형
	right90_output_img = make_right90(input_img, org_row, org_col); 
	right180_output_img = make_right180(input_img, org_row, org_col);
	left90_output_img = make_left90(input_img, org_row, org_col);
	Hor_mirror_output_img = make_Hor_mirror(input_img, org_row, org_col);
	Ver_mirror_output_img = make_Ver_mirror(input_img, org_row, org_col);

	//출력 파일 출력
	const char* output_file_right90 = in_file_name   right90_out_file_name".img";
	const char* output_file_right180 = in_file_name right180_out_file_name ".img";
	const char* output_file_left90 = in_file_name left90_out_file_name ".img";
	const char* output_file_Hor = in_file_name Hor_mirror_out_file_name  ".img";
	const char* output_file_Ver = in_file_name Ver_mirror_out_file_name  ".img";
	WriteFile_U(right90_output_img, output_file_right90, org_row, org_col);
	WriteFile_U(right180_output_img, output_file_right180, org_row, org_col);
	WriteFile_U(left90_output_img, output_file_left90, org_row, org_col);
	WriteFile_U(Hor_mirror_output_img, output_file_Hor, org_row, org_col);
	WriteFile_U(Ver_mirror_output_img, output_file_Ver, org_row, org_col);

	cout << "결과영상 출력" << endl;
	return 0;
}

