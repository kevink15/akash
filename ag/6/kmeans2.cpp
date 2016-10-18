
#include<iostream>
#include<cmath>
using namespace std;

float euclidean(float mean_x, float mean_y, float test_x, float test_y)
{
	float val=0;
	val=pow((mean_x-test_x), 2)+pow((mean_y-test_y), 2);
	return sqrt(val);
}

int main() {
	int i1, j1, i2, j2, i3, j3, t1;
	float t2_x, t2_y;
	float dist1, dist2;

	float k0[10][2];
	float k1[10][2];
	float k2[10][2];

	for (i1 = 0; i1 < 10; i1++) {
		for (j1=0;j1<2;j1++)
		{
		cout<<"Enter feature "<<j1<<" of item "<<i1<<endl;
		cin >> k0[i1][j1];
	}
}

	//initial means
	float m1_x, m1_y;
	float m2_x,m2_y;

	cout << "\n Enter X coordinate of initial mean 1:";
	cin >> m1_x;
		cout << "\n Enter Y coordinate of initial mean 1:";
	cin >> m1_y;

	cout << "\n Enter X coordinate of initial mean 2:";
	cin >> m2_x;

	cout << "\n Enter Y coordinate of initial mean 2:";
	cin >> m2_y;


	float om1_x, om1_y, om2_x, om2_y;    //old means

	do {

		//saving old means
		om1_x = m1_x;
		om2_x = m2_x;
		om1_x = m1_y;
		om2_y = m2_y;

		//creating clusters
		i1 = i2 = i3 = 0;
		for (i1 = 0; i1 < 10; i1++) {
			//calculating distance to means
			dist1 = euclidean(om1_x, om1_y, k0[i1][0], k0[i1][1]);
		
			dist2 = euclidean(om2_x, om2_y, k0[i1][0], k0[i1][1]);

			if (dist1 < dist2) {
				//near to first mean
				k1[i2][0] = k0[i1][0];
				k1[i2][1] = k0[i1][1];
				i2++;

			} else {
				//near to second mean
				k2[i3][0] = k0[i1][0];
				k2[i3][1] = k0[i1][1];
				i3++;
			}

}
		

		t2_x = 0;
		t2_y = 0;
		
		//calculating new mean
		for (t1 = 0; t1 < i2; t1++) {
			t2_x = t2_x + k1[t1][0];
			t2_y=t2_y+k1[t1][1];
		}
		m1_x = t2_x / i2;
		m1_y = t2_y / i2;

		t2_x = 0;
		t2_y = 0;
		for (t1 = 0; t1 < i3; t1++) {
			t2_x = t2_x + k2[t1][0];
			t2_y=t2_y+k2[t1][1];
		}
		m2_x = t2_x / i3;
		m2_y = t2_y / i3;

		//printing clusters
		cout << "\nCluster 1:"<<endl;
		for (j1= 0; j1 < i2; j1++) {
			cout<<k1[j1][0]<<", "<<k1[j1][1]<<endl;
		}
		cout << "\nm1=" << m1_x<<", "<<m1_y<<endl;

		cout << "\nCluster 2:"<<endl;
		for (j1 = 0; j1 < i3; j1++) {
			cout<<k2[j1][0]<<", "<<k2[j1][1]<<endl;
		}
		cout << "\nm2=" << m2_x<<", "<<m2_y<<endl;

		cout << "\n ----";
	} while (m1_x != om1_x && m2_x != om2_x && m1_y != om1_y && m2_y != om2_y);

	cout << "\n Clusters created";

	//ending

}

