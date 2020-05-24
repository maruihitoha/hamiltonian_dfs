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

	// dfs ����
	void dfs_main();

	// dfs ����
	void dfs_sub(int vertex);

	// ���� �湮�ߴ��� üũ
	bool chk_visited_all();

private :

	// ������ ��Ʈ������ �����ϴ� ����
	vector<string> string_container;

	// �����Ǵ� ��Ʈ��
	string generated_string;

	// ����Ʈ���� ���� ��Ʈ�� �迭
	string* spectrum;

	// ��������� ��Ÿ���� ������ �迭
	int** adjacency_matrix;

	// �湮 �� ���� ǥ���ϴ� �迭
	int* visited;

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
	this->visited = new int[arr_size];


	cout << "string size = " << str_size << endl;
	cout << "arr size = " << arr_size << endl;

	// ������� ���� �Ҵ�, ����Ʈ�� �迭 ����, �湮 �迭 �ʱ�ȭ
	for (int i = 0; i < arr_size; i++) 
	{
		this->spectrum[i] = input[i];
		this->adjacency_matrix[i] = new int[arr_size];
		visited[i] = 0;
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
	delete[] visited;
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

// �湮�� �� �Ǿ����� Ȯ���ϴ� �Լ�
bool hamiltonian::chk_visited_all()
{

	for (int i = 0; i < arr_size; i++)
	{
		if (this->visited[i] == 0)
			return false;
	}

	return true;
}

// dfs Ž���� �����ϴ� ���� �Լ�
void hamiltonian::dfs_main()
{

	// 0�� ��ġ���� �����ϴ� ���, 1�� ��ġ���� �����ϴ� ���.. ��� ��� ����
	for (int i = 0; i < arr_size; i++)
	{
		cout << i << " ��° �ε������� ����" << endl<<endl;

		generated_string = spectrum[i]; // �����ϴ� ����Ʈ��
		dfs_sub(i);						// dfs ����

		// ���� ��� �湮�� �߰�, ������ ��Ʈ���� ���̰� �ǵ��� �Ͱ� ������
		if (chk_visited_all() && (generated_string.length() == str_size + arr_size -1))
		{
			// ���� �� ��Ʈ�� �����̳ʿ� Ǫ��
			this->string_container.push_back(generated_string);
		}

		// �湮 �迭 �ʱ�ȭ
		for (int j = 0; j < arr_size; j++)
		{
			visited[j] = 0;
		}

		generated_string = "";
		cout << endl << endl;
	}

	// ���� �� ��Ʈ���� ���
	if (string_container.size() != 0)
	{
		for (int i = 0; i < string_container.size(); i++)
		{
			cout << i+1 <<".\t"<<string_container[i] << endl;
		}
		cout << endl << endl;
	}
	else
	{
		cout << "no string" << endl;
	}

}

// ��������� ������ ������ �����ϴ� dfs �Լ�
void hamiltonian:: dfs_sub(int vertex)
{
	int i;
	visited[vertex] = 1;
	for (i = 0; i < arr_size; i++)
	{
		if ((visited[i] == 0) && (adjacency_matrix[vertex][i] == 1))
		{
			cout << vertex << "����\t" << i << "\t�� �̵�" << endl;
			generated_string = generated_string + spectrum[i].substr(str_size-1, 1);
			dfs_sub(i);
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

	int size = sizeof(spectrum_01) / sizeof(spectrum_01[0]);
	hamiltonian* s_01 = new hamiltonian(spectrum_01, size);

	s_01->make_adj_matrix();
	s_01->show_matrix();
	s_01->dfs_main();
////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(spectrum_02) / sizeof(spectrum_02[0]);
	hamiltonian* s_02 = new hamiltonian(spectrum_02, size);

	s_02->make_adj_matrix();
	s_02->show_matrix();
	s_02->dfs_main();
////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(spectrum_03) / sizeof(spectrum_03[0]);
	hamiltonian* s_03 = new hamiltonian(spectrum_03, size);


	s_03->make_adj_matrix();
	s_03->show_matrix();
	s_03->dfs_main();
////////////////////////////////////////////////////////////////////////////////////
	size = sizeof(spectrum_04) / sizeof(spectrum_04[0]);
	hamiltonian* s_04 = new hamiltonian(spectrum_04, size);

	s_04->make_adj_matrix();
	s_04->show_matrix();
	s_04->dfs_main();
/////////////////////////////////////////////////////////////////////////////////////
	delete s_01;
	delete s_02;
	delete s_03;
	delete s_04;
}