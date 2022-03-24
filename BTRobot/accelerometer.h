#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

typedef struct {
	float x;
	float y;
	float z;
} accelerometer_vector;

void accelerometer_init(void);
accelerometer_vector accelerometer_read(void);

#endif
