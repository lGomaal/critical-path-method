#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

class Activities {
public:
	string name_of_entitiy;
	int duration_time;
	int Est;
	int Lst;
	int Efi;
	int Lfi;
	int num_of_predecessors_c;
	string depend[10];
};

Activities Network[100000];

void input_and_cala_half(int size)
{
	if (size < 2) {
		cout << " The amount of activity must be more than or equal to 2 !!!" << endl << endl;
		return;
	}

	for (int i = 0; i < size; i++)
	{
		Activities val;
		Activities find[100];
		int du, f = 0, z = 0;
		int num_of_predecessors;
		string id;
		cout << "plz enter the ID "<<i+1 <<" of the intitiy : ";
		cin >> id;
		val.name_of_entitiy = id;
		cout << "plz enter the duration time : ";
		cin >> du;
		val.duration_time = du;
		cout << "plz enter the number of the predecessors : ";
		cin >> num_of_predecessors;
		val.num_of_predecessors_c = num_of_predecessors;
		if (num_of_predecessors != 0) {
			for (int j = 0; j < num_of_predecessors; j++)
			{
				string ID_search;
				cout << "predecessor ID number " << j + 1 << " : ";
				cin >> ID_search;
				Network[i].depend[j] = ID_search;
				//enter the intitiy into new arr
				for (int l = 0; l < size; l++)
				{
					if (Network[l].name_of_entitiy == ID_search)
					{
						find[f].name_of_entitiy= Network[l].name_of_entitiy;
						find[f].duration_time = Network[l].duration_time;
						find[f].num_of_predecessors_c = Network[l].num_of_predecessors_c;
						find[f].Est = Network[l].Est;
						find[f].Efi = Network[l].Efi;
						f++;
					}
				}
			}
			//search for the biggist Els on the arr
			int max_comp_du = find[0].Efi, index1;
			for (int l = 0; l < f; l++)
			{
				if (max_comp_du <= find[l].Efi)
				{
					max_comp_du = find[l].Efi;
					index1 = l;
				}
			}
			Network[i].name_of_entitiy = val.name_of_entitiy;
			Network[i].duration_time = val.duration_time;
			Network[i].num_of_predecessors_c = val.num_of_predecessors_c;
			Network[i].Est = find[index1].Efi+1;
			Network[i].Efi = Network[i].duration_time + Network[i].Est-1;
			f = 0;
		}
		else
		{
			Network[i].name_of_entitiy = val.name_of_entitiy;
			Network[i].duration_time = val.duration_time;
			Network[i].num_of_predecessors_c = val.num_of_predecessors_c;
			Network[i].Est = 1;
			Network[i].Efi = Network[i].duration_time + Network[i].Est-1;
		}
	}
}

void calc_second_half(int size)
{
	Network[size - 1].Lst = Network[size - 1].Efi;
	Network[size - 1].Lfi = Network[size - 1].Lst - Network[size - 1].duration_time+1;
	for (int i = size - 2; i >= 0; i--)
	{
		bool cheak = true;
		for (int j = i; j < size; j++)
		{
			for (int w = 0; w < Network[j].num_of_predecessors_c; w++)
			{
				if (Network[i].name_of_entitiy == Network[j].depend[w])
				{
					cheak = false;
					break;
				}
			}
		}
		if (cheak == true)
		{
			Network[i].Lst = Network[i].Efi;
			Network[i].Lfi = Network[i].Lst - Network[i].duration_time;
		}
		else
		{
			Activities find1[100];
			int f = 0;
			for (int j = i; j < size; j++)
			{
				for (int w = 0; w < Network[j].num_of_predecessors_c; w++)
				{
					if (Network[i].name_of_entitiy == Network[j].depend[w])
					{
						find1[f].name_of_entitiy = Network[j].name_of_entitiy;
						find1[f].duration_time = Network[j].duration_time;
						find1[f].num_of_predecessors_c = Network[j].num_of_predecessors_c;
						find1[f].Est = Network[j].Est;
						find1[f].Efi = Network[j].Efi;
						find1[f].Lfi = Network[j].Lfi;
						find1[f].Lst = Network[j].Lst;
						f++;
					}
				}
			}
			int min_comp_du = find1[0].Lfi, index2;
			for (int l = 0; l < f; l++)
			{
				if (min_comp_du >= find1[l].Lfi)
				{
					min_comp_du = find1[l].Lfi;
					index2 = l;
				}
			}
			Network[i].Lst = min_comp_du-1;
			Network[i].Lfi = Network[i].Lst -  Network[i].duration_time+1;
			f = 0;
		}
	}
}

void finsh(int size)
{
	string answer ="";
	for (int i = 0; i < size; i++)
	{
		if (Network[i].Lst - Network[i].Efi == 0 && Network[i].Lfi - Network[i].Est == 0)
		{
			answer += Network[i].name_of_entitiy;
			answer += " ";
		}
	}
	cout << "The critical path is : ";
	cout << answer << endl;
}

void display(int size)
{
	for (int i = 0; i < size; i++) {
		cout << "ID of the intitiy : " << Network[i].name_of_entitiy << endl;
		cout << "the duration time : " << Network[i].duration_time << endl;
		cout << "Est : " << Network[i].Est << endl;
		cout << "Efi : " << Network[i].Efi << endl;
		cout << "Lst : " << Network[i].Lst << endl;
		cout << "Lfi : " << Network[i].Lfi << endl;
		for (int j = 0; j < Network[i].num_of_predecessors_c; j++)
		{
			cout << "Dependant number "<<j+1<<" : " << Network[i].depend[j] << endl;
		}
	}
}
int main()
{
	int siz;
	cout << "Input the number of activities: " << endl;
	cin >> siz;
	input_and_cala_half(siz);
	calc_second_half(siz);
	display(siz);
	finsh(siz);
	system("pause");
	return 0;
}