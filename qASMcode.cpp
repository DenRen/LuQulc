#include "Qulc.h"

int main () { 

	qRAM_t *_qRAM = new qRAM_t (10);

	qBit_t q0 ("1", _qRAM);
	qBit_t q1 ("0", _qRAM);
	q0 && q1 >>= getH & getH;
	q0 && q1 >>= funcAlgDD (1);
	q0 >>= getH;
	q0 <<= measure;
	
}