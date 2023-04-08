# Analysis-of-sequential-data

This program is a tool which can process signals that a sensor would 
give. The program uses data given at a particular timestamp.
It can process the signals in 2 different ways:
• The elimination of exceptions - done by going through the list of values, using 
a window of dimension n = 5(for simplicity) for which we compute average and 
deviation. will be eliminated the values that differs too much from the other 
from the values we work with at that time. First 2 and the last 2 values in the 
list are considered to be always correct.
![image](https://user-images.githubusercontent.com/130227711/230722437-0e93eb25-6291-444e-9a4d-b776596dee26.png)

If the values is not between it will be eliminated.

• Sometime intervals can contain more data than others. Ideally, we would like 
that frequency of the data to be constant, but due to the way of collection or 
due to the sensors, rarely this happens. We will try to move the data from high 
timestamps areas to areas with the lowest frequency. If the temporal 
difference between any two consecutive timestamps is in the interval is >= 1 
seconds, then the value for that data will be replaced with the value average 
between the previous data and the current data. We will do the same with the 
timestamp.
![image](https://user-images.githubusercontent.com/130227711/230722519-a96e9842-09a0-464b-8bb5-d13b0f1156d2.png)

We can always change what signal to work with ( give the program a 
differ input) or use the already processes signal.
To do all this I used 3 double-linked list, with specific function making use 
of dynamic allocation and some matemathical formulas previously mentioned
