# Manifold-Pressure-Monitor

This Arduino Project uses and Seeed XAIO microcontroller a BMP280 and a Adafruit MPRLS Ported Pressure Sensor  to measure the pressure in sampling system manifolds to alert technicians of change in pressure as well as to confirm period of sampling versus geration.

Manifold_Pressure2.ino uses a BMP280 to measure ambient pressue to give a true gauge reading
Manifold_Pressure.ino calculates gauge pressure by assuming ideal STP values at sea-level, this is more of an estimate and does not require the BMP sensor since ambient is assumed to be STP.
