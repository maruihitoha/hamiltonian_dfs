#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// �ع��� �н� ������ Ŭ����
class hamiltonian
{
public :
	// ������
	hamiltonian(string input[], int arrsize);

	~hamiltonian();

	// ���� ��� ����
	void make_adj_matrix();

	// ������� ���
	void show_matrix();

	// �̹� �ѹ� �Դ� ������ üũ
	bool chk_path_exists(int destination, int index);

	// ����� �н� ���ϴ� ����Լ� 
	bool hamilton_sub(int index);

	// �ع��� �н� ���� �Լ�
	void hamilton_main();

	// ������ ���� ������ �ִ��� ������ üũ
	bool chk_zero(int index);

private :

	// ��� ���� �迭
	int* path;

	// �����Ǵ� ��Ʈ��
	string generated_string;

	// ����Ʈ���� ���� ��Ʈ�� �迭
	string* spectrum;

	// ��������� ��Ÿ���� ������ �迭
	int** adjacency_matrix;

	// �Է� ���� ����Ʈ�� �迭�� ������ ������ ����Ʈ�� ��Ʈ���� ����
	int arr_size;
	int str_size;

};

// ������
hamiltonian::hamiltonian(string input[], int arrsize)
{

	this->arr_size = arrsize;
	this->spectrum = new string[arr_size];
	this->str_size = input[0].length();
	this->adjacency_matrix = new int*[arr_size];
	this->path = new int[arr_size];

	cout << "string size = " << str_size << endl;
	cout << "arr size = " << arr_size << endl;

	// ������� ���� �Ҵ�, ����Ʈ�� �迭 ����, ��� �迭 �ʱ�ȭ
	for (int i = 0; i < arr_size; i++) 
	{
		this->path[i] = -1;
		this->spectrum[i] = input[i];
		this->adjacency_matrix[i] = new int[arr_size];
		for (int j = 0; j < arr_size; j++)
		{
			this->adjacency_matrix[i][j] = 0;
		}
	}
	
}

// �Ҹ���
hamiltonian::~hamiltonian()
{
	for (int i = 0; i < arr_size; i++)
	{
		delete[] adjacency_matrix[i];
	}
	delete[] spectrum;
	delete[] path;
}

// ���� ��� ����
void hamiltonian:: make_adj_matrix()
{
	for (int i = 0; i < arr_size; i++)
	{
		for (int j = 0; j < arr_size; j++)
		{

			// i != j �̰�, ��� ���� n�� ����Ʈ���� 1���� �������� ���� ��Ʈ���� ���� ����Ʈ���� ���ۺ��� 
			// n-1������ ���꽺Ʈ���� ������ ���� ���� �� ������Ŀ� �߰�.
			if (i != j &&
				((this->spectrum[i]).substr(1, str_size-1 ) == (this->spectrum[j]).substr(0, str_size-1)))
			{
				this->adjacency_matrix[i][j] = 1;
			}

		}
	}

}


// ���� ��� ���
void hamiltonian::show_matrix()
{
	cout <<endl <<"\t\t";

	//��ȣ
	for (int i = 0; i < arr_size; i++)
	{
		cout << i <<" \t";
	}

	cout << endl << "\t\t";

	// ����Ʈ��
	for (int i = 0; i < arr_size; i++)
	{
		cout <<spectrum[i] << "\t";
	}

	cout << endl<<endl;

	// ��� ���� ����
	for (int i = 0; i < arr_size; i++)
	{

		cout << i << spectrum[i]<< "\t->\t";

		for (int j = 0; j < arr_size; j++)
		{
			cout << this->adjacency_matrix[i][j] << "\t";
		}

		cout << endl << endl;

	}
}


// ������ ���� ������ �ִ��� ������ üũ
bool hamiltonian::chk_zero(int index)
{
	int cnt = 0;
	for (int i = 0; i < arr_size; i++)
	{
		if (adjacency_matrix[index][i] == 1)
			return false;
	}
	return true;
}


// �̹� �ѹ� �Դ� ������ üũ
bool hamiltonian::chk_path_exists(int destination, int index)
{
	if (adjacency_matrix[ (path[index - 1]) ][destination] == 0)
		return false;

	for (int i = 0; i < index; i++)
	{
		if (path[i] == destination)
		{
			return false;
		}
	}

	return true;
}

bool hamiltonian::hamilton_sub(int index)
{
	// ���� �׷����� �����ϴ� ���ؽ��� �� ������ ���
	if (index == arr_size)
	{
		// ������ Ȯ��, ���� ��� true ��ȯ
		if (chk_zero(path[index - 1]))
			return true;
		else
			return false;
	}

	// ���� �ƴ� ���
	for (int v = 0; v < arr_size; v++)
	{
		// �̹� �ѹ� ������ ������ üũ, �ƴ� ��� ���� ����
		if (chk_path_exists(v, index))
		{
			path[index] = v;

			if (hamilton_sub(index + 1) == true)
				return true;

			// true ��ȯ �ȵ��� ��� ��� ����
			path[index] = -1;
		}
	}

	return false;
}


void hamiltonian::hamilton_main()
{

	// ���� �ε��� = path[0], �������� �ݺ������� ��� �����غ�
	for (int j = 0; j < arr_size; j++)
	{
		path[0] = j;

		// ��θ� ã���� ���
		if (hamilton_sub(1) == true)
		{
			string answer = spectrum[j];
			cout << "Path Found!! " << endl;
			cout << j << " ";
			for (int i = 1; i < arr_size; i++)
			{
				cout << path[i] << " ";
				answer = answer + spectrum[path[i]].substr(str_size - 1, 1);
			}
			cout << endl << answer << endl << endl;
		}
	}
}



// ���� �Լ�.
int main()
{
	string spectrum_01[8] = {"AGT", "AAA", "ACT", "AAC", "CTT", "GTA", "TTT", "TAA"};
	string spectrum_02[8] = {"ATG", "AGG", "TGC", "TCC", "GTC", "GGT", "GCA", "CAG"};
	string spectrum_03[8] = { "ATG", "TGG", "TGC", "GTG","GGC", "GCA", "GCG", "CGT" };
	string spectrum_04[13] = { "ATGC", "TGCG", "GCGG", "CGGC", "GGCT", "GCTG", 
							   "CTGT", "TGTA", "GTAT", "TATG", "ATGG", "TGGT", "GGTG" };

	// ���Ƿ� ���� ��Ʈ��
	string spectrum_05[9] = { "GAA", "ATC", "TCT", "AAG", "TCG", "CTT", "GTC", "AGT", "CGA" };

	int size = sizeof(spectrum_01) / sizeof(spectrum_01[0]);
	hamiltonian* s_01 = new hamiltonian(spectrum_01, size);

	s_01->make_adj_matrix();
	s_01->show_matrix();
	s_01->hamilton_main();

////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(spectrum_02) / sizeof(spectrum_02[0]);
	hamiltonian* s_02 = new hamiltonian(spectrum_02, size);

	s_02->make_adj_matrix();
	s_02->show_matrix();
	s_02->hamilton_main();

////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(spectrum_03) / sizeof(spectrum_03[0]);
	hamiltonian* s_03 = new hamiltonian(spectrum_03, size);


	s_03->make_adj_matrix();
	s_03->show_matrix();
	s_03->hamilton_main();

////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(spectrum_04) / sizeof(spectrum_04[0]);
	hamiltonian* s_04 = new hamiltonian(spectrum_04, size);

	s_04->make_adj_matrix();
	s_04->show_matrix();
	s_04->hamilton_main();

/////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(spectrum_05) / sizeof(spectrum_05[0]);
	hamiltonian* s_05 = new hamiltonian(spectrum_05, size);

	s_05->make_adj_matrix();
	s_05->show_matrix();
	s_05->hamilton_main();


	delete s_01;
	delete s_02;
	delete s_03;
	delete s_04;
	delete s_05;
}