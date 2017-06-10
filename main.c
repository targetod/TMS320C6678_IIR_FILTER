
#include <stdlib.h>
#include <math.h>
#include <ti/dsplib/dsplib.h>

// бібліотека з коефіцієнтами фільтру з МатЛабу
#include "fdacoefs.h"

/* Команда вибору пам*яті для даних */
//#pragma DATA_SECTION(in_s , " .EXT_RAM")


/* Global definitions */
/* Розмір масиву для відліків сигналу */
#define N 256

/* масив відліків вхідного сигналу та вихідного */
float   in_signal [N]; // для заповнення сигналом
float   out_signal [N]; // після  фільтрації

// матриця для збереження двох значень в лініях затримки секцій фільтрів
float delay[NUM_SECTIONS][SECTION_ORDER] = {0.0};



/*
    Функція генерує сигнал певної частоти і записує відліки в масив
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


	// формування коефіцієнтів b, a з файлу матлаб NUM i DEN  без коефіцієнтів підсилення
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

	// вказівники на вх і вих масиви
	inptr = in_signal;
	outptr = out_signal;

	/* Call IIR routine */
	// !вхідний масив портиться/змінюється
	 for(section = 0 ; section < NUM_SECTIONS ; section++)
	 {

		 DSPF_sp_biquad(inptr, &b[section][0], &a[section][0], &delay[section][0], outptr, N);

		 // для другої секції потрібен вихідний масив з першої секції
		 tempptr = outptr;
	    // вихідний стає вхідним першої секції, бо вхідний же не потрібен
		 outptr = inptr;
		 // вихідний першої секції робимо вхідним для другої
		 inptr = tempptr;
	  }

	 // формування вихідного сигналу враховуючи коеф підсилення з файлу матлаб
	 // якщо секцій парне число то вихідні дані знаходяться у вхідному масиві,
	 // а якщо непарне, то у вихідному масиві
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

    /* частота  дискретизації Hz*/
    FreqSample = 48000;

    /* Амплітуда сигналу */
    sinWaveMag = 2;

    /* частота  сигналу Hz*/
    FreqSignal = 2000;

    /* генерування сигналу */
	for (i = 0; i < N; i++) {
		in_signal[i]  = sinWaveMag * cos(2*3.14*i * FreqSignal /FreqSample)+
				sinWaveMag * cos(2*3.14*i*  (4*FreqSignal) /FreqSample) ;
	}

}




