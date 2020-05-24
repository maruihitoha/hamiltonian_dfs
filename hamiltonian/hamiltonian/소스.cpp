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

	// dfs 메인
	void dfs_main();

	// dfs 서브
	void dfs_sub(int vertex);

	// 전부 방문했는지 체크
	bool chk_visited_all();

private :

	// 생성된 스트링들을 저장하는 벡터
	vector<string> string_container;

	// 생성되는 스트링
	string generated_string;

	// 스펙트럼이 담기는 스트링 배열
	string* spectrum;

	// 인접행렬을 나타내는 이차원 배열
	int** adjacency_matrix;

	// 방문 한 곳을 표시하는 배열
	int* visited;

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
	this->visited = new int[arr_size];


	cout << "string size = " << str_size << endl;
	cout << "arr size = " << arr_size << endl;

	// 인접행렬 동적 할당, 스펙트럼 배열 생성, 방문 배열 초기화
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

// 소멸자
hamiltonian::~hamiltonian()
{
	for (int i = 0; i < arr_size; i++)
	{
		delete[] adjacency_matrix[i];
	}
	delete[] spectrum;
	delete[] visited;
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

// 방문이 다 되었는지 확인하는 함수
bool hamiltonian::chk_visited_all()
{

	for (int i = 0; i < arr_size; i++)
	{
		if (this->visited[i] == 0)
			return false;
	}

	return true;
}

// dfs 탐색을 시작하는 메인 함수
void hamiltonian::dfs_main()
{

	// 0의 위치에서 시작하는 경우, 1의 위치에서 시작하는 경우.. 등등 모두 실행
	for (int i = 0; i < arr_size; i++)
	{
		cout << i << " 번째 인덱스에서 시작" << endl<<endl;

		generated_string = spectrum[i]; // 시작하는 스펙트럼
		dfs_sub(i);						// dfs 시작

		// 만약 모두 방문을 했고, 생성된 스트링의 길이가 의도한 것과 같은지
		if (chk_visited_all() && (generated_string.length() == str_size + arr_size -1))
		{
			// 맞을 시 스트링 컨테이너에 푸시
			this->string_container.push_back(generated_string);
		}

		// 방문 배열 초기화
		for (int j = 0; j < arr_size; j++)
		{
			visited[j] = 0;
		}

		generated_string = "";
		cout << endl << endl;
	}

	// 생성 된 스트링들 출력
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

// 재귀적으로 스택의 역할을 수행하는 dfs 함수
void hamiltonian:: dfs_sub(int vertex)
{
	int i;
	visited[vertex] = 1;
	for (i = 0; i < arr_size; i++)
	{
		if ((visited[i] == 0) && (adjacency_matrix[vertex][i] == 1))
		{
			cout << vertex << "에서\t" << i << "\t로 이동" << endl;
			generated_string = generated_string + spectrum[i].substr(str_size-1, 1);
			dfs_sub(i);
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