/*
 * Discrete-Time IIR Filter (real)
 * -------------------------------
 * Filter Structure    : Direct-Form II Transposed, Second-Order Sections
 * Number of Sections  : 2
 * Stable              : Yes
 * Linear Phase        : No
 */
// в даному випадку Direct-Form II Transposed та Direct-Form II Transposed мають однаковий вид

/* масив коефіцієнтів фільтру */
//   3000-4000  fs - 48000  FNCH

// Число секцій НІХ фільтра
#define NUM_SECTIONS 2

// Порядок секції одного фільтра -> Second-Order
#define SECTION_ORDER 2

// коефіцієнти оримані з програми МАТЛАБ
#define MWSPT_NSEC 5

const int NL[MWSPT_NSEC] = { 1,3,1,3,1 };
const float NUM[MWSPT_NSEC][3] = {
  {
    0.09870222211,              0,              0 // <- Numerator gain for section #1
  },
  {
                1,              2,              1 // <- Numerator for section #1
  },
  {
    0.03091436252,              0,              0 // <- Numerator gain for section #2
  },
  {
                1,              2,              1 // <- Numerator for section #2
  },
  {
     0.9440608621,              0,              0 // <- Gain for output
  }
};
const int DL[MWSPT_NSEC] = { 1,3,1,3,1 };
const float DEN[MWSPT_NSEC][3] = {
  {
                1,              0,              0 // <- Denominator gain for section #1
  },
  {
                1,   -1.413424015,   0.8082329631 // <- Denominator for section #1
  },
  {
                1,              0,              0 // <- Denominator gain for section #2
  },
  {
                1,   -1.443653464,   0.5673109293 // <- Denominator for section #2
  },
  {
                1,              0,              0 // <- Output gain for section #3
  }
};





