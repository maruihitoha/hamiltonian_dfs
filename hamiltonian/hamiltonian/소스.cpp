#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// 해밀턴 패스 수행할 클래스
class hamiltonian
{
public :
	// 생성자
	hamiltonian(string input[], int arrsize);

	~hamiltonian();

	// 인접 행렬 생성
	void make_adj_matrix();

	// 인접행렬 출력
	void show_matrix();

	// 이미 한번 왔던 곳인지 체크
	bool chk_path_exists(int destination, int index);

	// 헤밀턴 패스 구하는 재귀함수 
	bool hamilton_sub(int index);

	// 해밀턴 패스 메인 함수
	void hamilton_main();

	// 도착한 곳에 갈곳이 있는지 없는지 체크
	bool chk_zero(int index);

private :

	// 경로 저장 배열
	int* path;

	// 생성되는 스트링
	string generated_string;

	// 스펙트럼이 담기는 스트링 배열
	string* spectrum;

	// 인접행렬을 나타내는 이차원 배열
	int** adjacency_matrix;

	// 입력 받은 스펙트럼 배열의 원소의 갯수와 스펙트럼 스트링의 길이
	int arr_size;
	int str_size;

};

// 생성자
hamiltonian::hamiltonian(string input[], int arrsize)
{

	this->arr_size = arrsize;
	this->spectrum = new string[arr_size];
	this->str_size = input[0].length();
	this->adjacency_matrix = new int*[arr_size];
	this->path = new int[arr_size];

	cout << "string size = " << str_size << endl;
	cout << "arr size = " << arr_size << endl;

	// 인접행렬 동적 할당, 스펙트럼 배열 생성, 경로 배열 초기화
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

// 소멸자
hamiltonian::~hamiltonian()
{
	for (int i = 0; i < arr_size; i++)
	{
		delete[] adjacency_matrix[i];
	}
	delete[] spectrum;
	delete[] path;
}

// 인접 행렬 생성
void hamiltonian:: make_adj_matrix()
{
	for (int i = 0; i < arr_size; i++)
	{
		for (int j = 0; j < arr_size; j++)
		{

			// i != j 이고, 출발 길이 n인 스펙트럼의 1부터 끝까지의 서브 스트링과 도착 스펙트럼의 시작부터 
			// n-1까지의 서브스트링이 같은지 비교후 같을 시 인접행렬에 추가.
			if (i != j &&
				((this->spectrum[i]).substr(1, str_size-1 ) == (this->spectrum[j]).substr(0, str_size-1)))
			{
				this->adjacency_matrix[i][j] = 1;
			}

		}
	}

}


// 인접 행렬 출력
void hamiltonian::show_matrix()
{
	cout <<endl <<"\t\t";

	//번호
	for (int i = 0; i < arr_size; i++)
	{
		cout << i <<" \t";
	}

	cout << endl << "\t\t";

	// 스펙트럼
	for (int i = 0; i < arr_size; i++)
	{
		cout <<spectrum[i] << "\t";
	}

	cout << endl<<endl;

	// 경로 존재 유무
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


// 도착한 곳에 갈곳이 있는지 없는지 체크
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


// 이미 한번 왔던 곳인지 체크
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
	// 만약 그래프의 존재하는 버텍스를 다 돌았을 경우
	if (index == arr_size)
	{
		// 끝인지 확인, 끝일 경우 true 반환
		if (chk_zero(path[index - 1]))
			return true;
		else
			return false;
	}

	// 끝이 아닐 경우
	for (int v = 0; v < arr_size; v++)
	{
		// 이미 한번 갔었던 곳인지 체크, 아닐 경우 동작 수행
		if (chk_path_exists(v, index))
		{
			path[index] = v;

			if (hamilton_sub(index + 1) == true)
				return true;

			// true 반환 안됐을 경우 경로 삭제
			path[index] = -1;
		}
	}

	return false;
}


void hamiltonian::hamilton_main()
{

	// 시작 인덱스 = path[0], 시작점은 반복문으로 모두 수행해봄
	for (int j = 0; j < arr_size; j++)
	{
		path[0] = j;

		// 경로를 찾았을 경우
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



// 메인 함수.
int main()
{
	string spectrum_01[8] = {"AGT", "AAA", "ACT", "AAC", "CTT", "GTA", "TTT", "TAA"};
	string spectrum_02[8] = {"ATG", "AGG", "TGC", "TCC", "GTC", "GGT", "GCA", "CAG"};
	string spectrum_03[8] = { "ATG", "TGG", "TGC", "GTG","GGC", "GCA", "GCG", "CGT" };
	string spectrum_04[13] = { "ATGC", "TGCG", "GCGG", "CGGC", "GGCT", "GCTG", 
							   "CTGT", "TGTA", "GTAT", "TATG", "ATGG", "TGGT", "GGTG" };

	// 임의로 만든 스트링
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