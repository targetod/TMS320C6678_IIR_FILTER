
#include <stdlib.h>
#include <math.h>
#include <ti/dsplib/dsplib.h>

// �������� � ������������� ������� � �������
#include "fdacoefs.h"

/* ������� ������ ���*�� ��� ����� */
//#pragma DATA_SECTION(in_s , " .EXT_RAM")


/* Global definitions */
/* ����� ������ ��� ����� ������� */
#define N 256

/* ����� ����� �������� ������� �� ��������� */
float   in_signal [N]; // ��� ���������� ��������
float   out_signal [N]; // ����  ����������

// ������� ��� ���������� ���� ������� � ���� �������� ������ �������
float delay[NUM_SECTIONS][SECTION_ORDER] = {0.0};



/*
    ������� ������ ������ ����� ������� � ������ ����� � �����
*/
void generateInput ();




int main(void) {
	int i,j, section;

	float *inptr, *outptr, *tempptr;
	float b[NUM_SECTIONS][SECTION_ORDER+1]; // coef
	float a[NUM_SECTIONS][SECTION_ORDER+1]; // coef
	float G = 1.0; // total gain
	/* Generate the input data */
	generateInput();


	// ���������� ����������� b, a � ����� ������ NUM i DEN  ��� ����������� ���������
	for (i = 0 ; i < NUM_SECTIONS; ++i){
		for (j = 0; j < SECTION_ORDER+1; j++  ){
			b[i][j] = NUM[i*NUM_SECTIONS+1][j];
			a[i][j] = DEN[i*NUM_SECTIONS+1][j];
		}
	}

	// total gain numerator
	for (i = 0 ; i < NUM_SECTIONS+1; ++i){
		G *= NUM[i*NUM_SECTIONS][0];
	}

	// ��������� �� �� � ��� ������
	inptr = in_signal;
	outptr = out_signal;

	/* Call IIR routine */
	// !������� ����� ���������/���������
	 for(section = 0 ; section < NUM_SECTIONS ; section++)
	 {

		 DSPF_sp_biquad(inptr, &b[section][0], &a[section][0], &delay[section][0], outptr, N);

		 // ��� ����� ������ ������� �������� ����� � ����� ������
		 tempptr = outptr;
	    // �������� ��� ������� ����� ������, �� ������� �� �� �������
		 outptr = inptr;
		 // �������� ����� ������ ������ ������� ��� �����
		 inptr = tempptr;
	  }

	 // ���������� ��������� ������� ���������� ���� ��������� � ����� ������
	 // ���� ������ ����� ����� �� ������ ��� ����������� � �������� �����,
	 // � ���� �������, �� � ��������� �����
	 for(i = 0 ; i < N ; i++){
		 out_signal[i] = G * (NUM_SECTIONS%2==0 ? in_signal[i] : out_signal[i] ) ;
	 }



	i=0;// breakpoint

	return 0;
}


void generateInput () {
    int   i;
    float FreqSample, sinWaveMag;
    int FreqSignal;

    /* �������  ������������� Hz*/
    FreqSample = 48000;

    /* �������� ������� */
    sinWaveMag = 2;

    /* �������  ������� Hz*/
    FreqSignal = 2000;

    /* ����������� ������� */
	for (i = 0; i < N; i++) {
		in_signal[i]  = sinWaveMag * cos(2*3.14*i * FreqSignal /FreqSample)+
				sinWaveMag * cos(2*3.14*i*  (4*FreqSignal) /FreqSample) ;
	}

}




