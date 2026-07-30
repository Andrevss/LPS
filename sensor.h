#ifndef SENSOR_H
#define SENSOR_H

void sensor_init(void);
float sensor_read_temperature(void);
float sensor_read_pressure(void);
void sensor_calibrate(void);

#endif // SENSOR_H
