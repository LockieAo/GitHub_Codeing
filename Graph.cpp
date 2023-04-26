/*
ͼ��

���ࣺ����ͼ������ͼ

����ͼ�洢�ṹ���ڽӾ���

����ͼ�洢�ṹ���ڽӾ����ڽӱ�����߱������߱���

ͼ�ı�����ʽ��������ȣ�DFS��������ȣ�BFS��

��С��������Kruskal�㷨 Prim�㷨

���·����

��Դ���·�����޸�Ȩ Dijkstra�㷨

��Դ���·�����и�Ȩ Bellman-Ford�㷨

��Դ���·����Floyd-Warshall�㷨


*/
#pragma once
#include"Union_Find_Set.hpp"
#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<functional>
using namespace std;

//�ڽӱ�
namespace link_table {
	//�ڽӱ���㣨���߱���
	template<typename W>
	struct EdgeOut {
		int _desti;//Ŀ�����±�
		W _weight;//Ȩֵ
		EdgeOut<W>* _next;//ָ����һ������ָ��

		EdgeOut(int desti, const W& weight)
			:_desti(desti)
			, _weight(weight)
			, _next(nullptr)
		{}
	};

	//�ڽӱ���㣨��߱���
	template<typename W>
	struct EdgeIn {
		int _srcti;//Դ����±�
		W _weight;//Ȩֵ
		EdgeIn<W>* _next;//ָ����һ������ָ��

		EdgeIn(int _srcti, const W& weight)
			:_srcti(_srcti)
			, _weight(weight)
			, _next(nullptr)
		{}
	};

	//ģ�������V���������ͣ�W��Ȩֵ���ͣ�MAX_W��Ȩֵ��Ĭ��ֵ��Direction����ʾ�Ƿ�������ͼ��Ĭ��������ͼ��
	template<typename V, typename W, W MAX_W = INT_MAX, bool Direction = false>
	class Graph {
		typedef EdgeOut<W> EdgeOut;
		typedef EdgeIn<W> EdgeIn;
	private:
		//��һά����洢����
		vector<V> _vertex;

		//�ù�ϣ���洢������±��ӳ��
		unordered_map<V, int> _indexMap;
		
		//ʹ������洢�ڽӱ� ���߱�
		vector<EdgeOut*> _outTables;

		//��߱�
		vector<EdgeIn*> _inTables;
	public:
		//����Ĭ�Ϲ���
		Graph() = default;

		//�Զ��幹��ͼ
		Graph(const V* a, size_t n) {
			//�洢�����ӳ��
			//_vertex.reserve(n);
			for (int i = 0; i < n; i++) {
				_vertex.push_back(a[i]);
				_indexMap[a[i]] = i;
			}

			//��ʼ���ڽӱ�
			_outTables.resize(n,nullptr);
			_inTables.resize(n,nullptr);
		}

		//��ȡ�����Ӧ���±�
		size_t GetVertexIndex(const V& value) {
			auto it = _indexMap.find(value);

			if (it == _indexMap.end()) {
				cout << value << " ���㲻����" << endl;
				return -1;
			}
			else {
				return it->second;
			}

			return -1;
		}

		//���ڽӱ������ӱ�
		void _AddEdge(size_t srci, size_t desti, const W& weight) {

			//���³��߱�
			EdgeOut*edgeOut = new EdgeOut(desti,weight);
			edgeOut->_next = _outTables[srci];
			_outTables[srci] = edgeOut;

			//������߱�
			EdgeIn* edgeIn = new EdgeIn(srci, weight);
			edgeIn->_next = _inTables[desti];
			_inTables[desti] = edgeIn;

			//���������ͼ��˫������Ҫ����
			if (Direction == false) {
				//���³��߱�
				EdgeOut* egOut = new EdgeOut(srci,weight);
				egOut->_next = _outTables[desti];
				_outTables[desti] = egOut;

				//������߱�
				EdgeIn* egIn = new EdgeIn(desti, weight);
				egIn->_next = _inTables[srci];
				_inTables[srci] = egIn;
			}
		}

		void AddEdge(const V& sour, const V& dest, const W& weight) {
			size_t srci = GetVertexIndex(sour);
			size_t desti = GetVertexIndex(dest);

			_AddEdge(srci, desti, weight);
		}



		//��ӡ
		void Print() {
			//����
			for (int i = 0; i < _vertex.size(); i++) {
				cout << _vertex[i] << " ";
			}
			cout << endl << endl;

			//�����±�
			cout << "  ";
			for (int i = 0; i < _vertex.size(); i++) {
				printf("%4d", i);
			}
			cout << endl << endl;

			//�ڽӱ� ���߱�
			for (int i = 0; i < _outTables.size(); i++) {
				cout << "[" << _vertex[i] << "]->";
				EdgeOut* edge = _outTables[i];
				while (edge) {
					cout << "[" << _vertex[edge->_desti] << ":" << edge->_weight << "]->";
					edge = edge->_next;
				}
				cout << "nullptr" << endl;
			}

			cout << endl;

			//�ڽӱ� ��߱�
			for (int i = 0; i < _inTables.size(); i++) {
				
				EdgeIn* edge = _inTables[i];
				cout << "[" << _vertex[i] << "]" ;
				while (edge) {
					cout << "<-[" << _vertex[edge->_srcti] << ":" << edge->_weight << "]";
					edge = edge->_next;
				}
				cout << endl;
				
				//
			}
		}

	};
}


//�ڽӾ���
namespace matrix {
	//ģ�������V���������ͣ�W��Ȩֵ���ͣ�MAX_W��Ȩֵ��Ĭ��ֵ��Direction����ʾ�Ƿ�������ͼ��Ĭ��������ͼ��
	template<typename V, typename W, W MAX_W = INT_MAX, bool Direction = false>
	class Graph {
		typedef Graph<V, W, MAX_W, Direction> Self;
	private:
		//��һά����洢����
		vector<V> _vertex;

		//�ù�ϣ���洢������±��ӳ��
		unordered_map<V, int> _indexMap;

		//�ö�ά����洢�ڽӾ���
		vector<vector<W>> _matrix;
	public:
		//����Ĭ�Ϲ���
		Graph() = default;

		//�Զ��幹��ͼ
		Graph(const V* a, size_t n) {
			//�洢�����ӳ��
			//_vertex.reserve(n);
			for (int i = 0; i < n; i++) {
				_vertex.push_back(a[i]);
				_indexMap[a[i]] = i;
			}

			//��ʼ���ڽӾ���
			_matrix.resize(n);
			for (int i = 0; i < n; i++) {
				_matrix[i].resize(n, MAX_W);
			}

			//�Ƿ���Ҫ�������������ľ������Ϊ0
			/*
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) {
						_matrix[i][j] = 0;
					}
				}
			}
			*/

		}

		//��ȡ�����Ӧ���±�
		size_t GetVertexIndex(const V& value) {
			auto it = _indexMap.find(value);

			if (it == _indexMap.end()) {
				cout << value << "���㲻����" << endl;
				return -1;
			}
			else {
				return it->second;
			}

			return -1;
		}

		//��ͼ�����ӱ�
		void _AddEdge(size_t srci, size_t desti, const W& weight) {
			_matrix[srci][desti] = weight;

			//���������ͼ��˫������Ҫ����
			if (Direction == false) {
				_matrix[desti][srci] = weight;
			}
		}

		void AddEdge(const V& sour, const V& dest, const W& weight) {
			size_t srci = GetVertexIndex(sour);
			size_t desti = GetVertexIndex(dest);

			_AddEdge(srci, desti, weight);
		}


		//��ĳһ�㿪ʼ��ȱ���
		void BFS(const V& sour) {
			//��ȡ�õ���±�
			int souri = GetVertexIndex(sour);

			//������飬������Ǹý���Ƿ������
			vector<bool> flag(_vertex.size(),false);

			//���У������洢���������Ľ��
			queue<int> q;

			//����ʼ���������
			q.push(souri);

			while (!q.empty()) {
				int size = q.size();

				while (size--) {
					//��ȡ��ͷ���
					int index = q.front();
					q.pop();
					cout << _vertex[index] << " ";
					
					//��ȡ�ý��������û�б������Ľ��
					for (int i = 0; i < _vertex.size(); i++) {
						if (_matrix[index][i] != MAX_W && flag[i] == false) {
							q.push(i);
							flag[i] = true;
						}
					}
				}

				cout << endl;
			}
		}

		void _DFS(int index,vector<bool>& flag) {
			cout << _vertex[index] <<endl;
			flag[index] = true;

			for (int i = 0; i < _vertex.size(); i++) {
				if (_matrix[index][i] != MAX_W && flag[i] == false) {
					_DFS(i,flag);
				}
			}
		}
		
		//��ĳһ�㿪ʼ��ȱ���
		void DFS(const V& sour) {
			int souri = GetVertexIndex(sour);

			//�������
			vector<bool> flag(_vertex.size(),false);

			_DFS(souri,flag);
		}
		

		//�����ж�����࣬����洢����㼰Ȩֵ
		struct Edge {
			int _souri;
			int _desti;
			W _weight;

			Edge(size_t souri,size_t desti,const W& weight)
				:_souri(souri)
				,_desti(desti)
				,_weight(weight)
			{}

			bool operator>(const Edge& e)const
			{
				return _weight > e._weight;
			}
		};

		//��С������ Kruskal�㷨 ����ͼ
		W Kruskal(Self& minTree) {
			size_t n = _vertex.size();

			minTree._indexMap = _indexMap;
			minTree._matrix = _matrix;
			minTree._vertex = _vertex;

			//�����ڽӾ���
			for (int i = 0; i < n; i++) {
				minTree._matrix[i].resize(n,MAX_W);
			}

			//������С��
			priority_queue<Edge, vector<Edge>, greater<Edge>> minque;

			//���ߴ�����С��
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					//����������ͼ�����ֻ��Ҫ��һ��
					if (i < j && _matrix[i][j] != MAX_W) {
						minque.push(Edge(i,j,_matrix[i][j]));
					}
				}
			}

			//���岢�鼯
			UnionFindSet<int> ufs(n,-1);

			//n�����㣬��С������n-1����,size��¼�ҵ��ķ���Ҫ��ıߵ���Ŀ
			int size = 0;

			//�洢��С������Ȩֵ
			W target = W();

			while (!minque.empty()) {
				Edge eg = minque.top();
				minque.pop();

				//���ж����������������Ƿ���ͬһ������
				if (!ufs.Inset(eg._souri,eg._desti)) {
					//����ͬһ������
					//cout <<"�ڵ���Ϣ��" << _vertex[eg._souri]<< " "<<_vertex[eg._desti] << " " << eg._weight << endl;
					minTree._AddEdge(eg._souri, eg._desti,eg._weight);
					ufs.Union(eg._souri, eg._desti);
					size++;
					target += eg._weight;
				}
				else {
					//��ͬһ������
				}
			}

			if (size == n - 1) {
				//cout << target << endl;
				return target;
			}

			return W();

		}

		//��С������ Prim�㷨 ����ͼ
		W Prim(Self& minTree,const W& sour) {
			//��ȡ��ʼ����±�
			size_t souri = GetVertexIndex(sour);

			size_t n = _vertex.size();
			minTree._indexMap = _indexMap;
			minTree._matrix = _matrix;
			minTree._vertex = _vertex;

			//�����ڽӾ���
			for (int i = 0; i < n; i++) {
				minTree._matrix[i].resize(n, MAX_W);
			}

			//�������
			//X��Ǹý���ǲ����Ѿ���ѡ�񣬱�ѡ����Ϊtrue
			vector<bool> X(n,false);

			//Y��Ǹý���ǲ��ǻ�û�б�ѡ��û�б�ѡ����Ϊfalse
			vector<bool> Y(n,true);

			X[souri] = true;
			Y[souri] = false;

			//������С��
			priority_queue<Edge,vector<Edge>,greater<Edge>> minque;

			//ѡ���뿪ʼ�����������С�ߣ����Ȱ��뿪ʼ������������б����ӽ�����С��
			for (int i = 0; i < n; i++) {
				if (_matrix[souri][i] != MAX_W) {
					minque.push(Edge(souri, i, _matrix[souri][i]));
				}
			}

			//ѡ��ߣ�size�����Ѿ�ѡ���ıߵĸ���
			int size = 0;
			W target = W();

			while (!minque.empty()) {
				Edge eg = minque.top();
				minque.pop();

				if (X[eg._desti]) {
					//�����ߵ�Ŀ�����Ѿ���ѡ�񣬲�����ѡ��
				}
				else {
					//�����ߵ�Ŀ����û�б�ѡ��

					minTree._AddEdge(eg._souri, eg._desti, eg._weight);
					cout << "�ڵ���Ϣ��" << _vertex[eg._souri] << " " << _vertex[eg._desti] << " " << eg._weight << endl;
					target += eg._weight;

					//�ý����ѡ�񣬽��б��
					X[eg._desti] = true;

					Y[eg._desti] = false;

					size++;

					if (size == n - 1) {
						break;
					}

					//�����Ŀ��������������û�б�ѡ��ı�ȫ�����ӽ�����С��
					for (int i = 0; i < n; i++) {
						//���ñߴ��ڣ���Ŀ���㲢û�б�ѡ���
						if (_matrix[eg._desti][i] != MAX_W && Y[i]) {
							minque.push(Edge(eg._desti, i, _matrix[eg._desti][i]));
						}
					}
				}
			}

			if (size == n - 1) {
				//cout << target << endl;
				return target;
			}

			return W();

		}

		//��Դ���·�����޸�Ȩ Dijkstra�㷨
		//sour��Դ��� destWieght��Դ�ڵ㵽��������Ŀǰ�����·�� pPath�����浱ǰ�±�Ľ��ĸ��ڵ�
		void Dijkstra(const V& sour, vector<W>& destWieght, vector<int>& pPath) {
			//��ȡԴ�ڵ��±�
			size_t souri = GetVertexIndex(sour);

			//��ȡ������
			size_t n = _vertex.size();

			//��ʼ������
			destWieght.resize(n,MAX_W);
			pPath.resize(n,-1);

			//Դ�ڵ㵽�Լ���·����0
			destWieght[souri] = 0;
			pPath[souri] = souri;

			//S��Ǹý���Ƿ��ҵ����·��
			vector<bool> S(n,false);

			//ÿ��ѡ��һ�����·����ѡn��
			for (int i = 0; i < n; i++) {
				//ѡ��һ����ǰ��û���ҵ����·�����Ҿ���Դ�ڵ�·����̵Ľ��
				//u��������Ѱ�ҵ��Ľ���±�
				int u = 0;
				//min�����ӦȨֵ
				W min = MAX_W;
				for (int j = 0; j < n; j++) {
					if (S[j] == false && destWieght[j] < min) {
						u = j;
						min = destWieght[j];
					}
				}

				//�ҵ���Դ�ڵ��������
				S[u] = true;
				//�����ɳڲ������ѵ�ǰ��û���ҵ����·���Ľ�㵽Դ�ڵ����̾�����и���
				for (int v = 0; v < n; v++) {
					if (S[v] == false && _matrix[u][v] != MAX_W && (destWieght[u] + _matrix[u][v]) < destWieght[v]) {
						destWieght[v] = destWieght[u] + _matrix[u][v];
						pPath[v] = u;
					}
				}

			}

		}

		//��Դ���·����Bellman-Ford�㷨������Ȩ
		bool Bellman_Ford(const V& sour, vector<W>& destWieght, vector<int>& pPath) {
			//��ȡԴ�ڵ��±�
			size_t souri = GetVertexIndex(sour);

			//��ȡ������
			size_t n = _vertex.size();

			//��ʼ������
			destWieght.resize(n, MAX_W);
			pPath.resize(n, -1);


			destWieght[souri] = W();

			//�����ǰ���޸������·�������ܻ�Ӱ������������·���������Ҫ��һ�ֽ��и�����
			//������n�֣���Ϊֻ��n����㣬����n�ָ��������󣬻���и�Ȩ��·�жϡ�
			for (int k = 0; k < n;k++) {
				//������Ǳ����Ƿ����
				bool update = false;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {

						if (_matrix[i][j] != MAX_W && (destWieght[i] + _matrix[i][j]) < destWieght[j]) {
							destWieght[j] = destWieght[i] + _matrix[i][j];
							pPath[j] = i;
							//���±�־
							update = true;
						}
					}
				}

				if (update == false) {
					break;
				}
			}

			//�ж��Ƿ��и�Ȩ��·��Ҳ�����ж��Ƿ񻹿��Ը���
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {

					if (_matrix[i][j] != MAX_W && (destWieght[i] + _matrix[i][j]) < destWieght[j]) {
						return false;
					}
				}
			}

			return true;
		}

		//��Դ���·����Floyd-Warshall�㷨
		//vvDestWeight����i��j��Ȩֵ vvpPath����i��j�����·����j��ǰһ������±�
		void Floyd_Warshall(vector<vector<W>>& vvDestWeight, vector<vector<int>>& vvpPath) {
			//��ȡ������
			size_t n = _vertex.size();

			//�޸ľ���Ԫ�ظ���
			vvDestWeight.resize(n);
			vvpPath.resize(n);

			//��ʼ������
			for (int i = 0; i < n; i++) {
				vvDestWeight[i].resize(n,MAX_W);
				vvpPath[i].resize(n,-1);
			}

			//������ֵ
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					//����i��j��ֱ��������
					if (_matrix[i][j] != MAX_W) {
						//��ȡ��i��j��Ȩֵ
						vvDestWeight[i][j] = _matrix[i][j];
						//��i��jֱ����ͨ�����j��ǰһ������±���i
						vvpPath[i][j] = i;
					}
					//�����ͬһ���ڵ㣬��Ȩֵ����ΪĬ��ֵ
					if (i == j) {
						vvDestWeight[i][j] = W();
					}
				}
			}

			//�������·������
			//k���м���
			for (int k = 0; k < n; k++) {
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						//�����i��k��·�� ��k��j��·�� �Ҵ�i��k��j��Ȩֵ��ԭ�ȴ�i��j�̣����и���
						if (vvDestWeight[i][k] != MAX_W && vvDestWeight[k][j] != MAX_W && (vvDestWeight[i][k] + vvDestWeight[k][j]) < vvDestWeight[i][j]) {
							vvDestWeight[i][j] = vvDestWeight[i][k] + vvDestWeight[k][j];
							vvpPath[i][j] = vvpPath[k][j];
						}
					}
				}
			}
		}
		
		//��ӡ���·��
		void PrinrtShotPath(const V& sour, const vector<W>& destWieght, const vector<int>& pPath) {
			size_t souri = GetVertexIndex(sour);
			size_t n = destWieght.size();

			for (int i = 0; i < n; i++) {
				if (i != souri) {
					//�洢Դ�ڵ㵽�ý��·��
					vector<int> path;
					//�洢�ý������·������һ�����
					size_t pi = i;

					while (pi != souri) {
						path.push_back(pi);
						pi = pPath[pi];
					}

					path.push_back(souri);

					reverse(path.begin(),path.end());

					for (auto& e : path) {
						cout << _vertex[e] << "->";
					}

					cout << "��·��Ȩֵ�ͣ�" << destWieght[i]<<endl;
				}
			}
		}


		//��ӡ
		void Print() {
			//����
			for (int i = 0; i < _vertex.size(); i++) {
				cout << _vertex[i] << " ";
			}
			cout << endl << endl;

			//�����±�
			cout << "  ";
			for (int i = 0; i < _vertex.size(); i++) {
				printf("%4d", i);
			}
			cout << endl << endl;
			//�ڽӾ���
			for (int i = 0; i < _matrix.size(); i++) {
				cout << i << " ";
				for (int j = 0; j < _matrix[i].size(); j++) {
					if (_matrix[i][j] == MAX_W) {
						printf("%4c", '*');
					}
					else {
						printf("%4d", _matrix[i][j]);
					}
				}
				cout << endl;
			}
			cout << endl << endl;

			//��ӡԴ��->Ŀ�ĵ㣨Ȩֵ��
			for (int i = 0; i < _matrix.size(); i++) {
				for (int j = 0; j < _matrix[i].size(); j++) {
					if (i != j && _matrix[i][j] != MAX_W) {
						cout << _vertex[i] << "->" << _vertex[j] << " [" << _matrix[i][j] << "]" << endl;
					}
				}
			}

			cout << endl;
		}

	};
}

void TestGraphDijkstra()
{
	const char* str = "syztx";
	matrix::Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('s', 't', 10);
	g.AddEdge('s', 'y', 5);
	g.AddEdge('y', 't', 3);
	g.AddEdge('y', 'x', 9);
	g.AddEdge('y', 'z', 2);
	g.AddEdge('z', 's', 7);
	g.AddEdge('z', 'x', 6);
	g.AddEdge('t', 'y', 2);
	g.AddEdge('t', 'x', 1);
	g.AddEdge('x', 'z', 4);
	vector<int> dist;
	vector<int> parentPath;
	g.Dijkstra('s', dist, parentPath);
	g.PrinrtShotPath('s', dist, parentPath);
}

void TestGraphBellmanFord()
{
	const char* str = "syztx";
	matrix::Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('s', 't', 6);
	g.AddEdge('s', 'y', 7);
	g.AddEdge('y', 'z', 9);
	g.AddEdge('y', 'x', -3);
	g.AddEdge('z', 's', 2);
	g.AddEdge('z', 'x', 7);
	g.AddEdge('t', 'x', 5);
	g.AddEdge('t', 'y', 8);
	g.AddEdge('t', 'z', -4);
	g.AddEdge('x', 't', -2);
	vector<int> dist;
	vector<int> parentPath;
	if (g.Bellman_Ford('s', dist, parentPath))
	{
		g.PrinrtShotPath('s', dist, parentPath);
	}
	else
	{
		cout << "���ڸ�Ȩ��·" << endl;
	}
}

void TestFloydWarShall()
{
	const char* str = "12345";
	matrix::Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('1', '2', 3);
	g.AddEdge('1', '3', 8);
	g.AddEdge('1', '5', -4);
	g.AddEdge('2', '4', 1);
	g.AddEdge('2', '5', 7);
	g.AddEdge('3', '2', 4);
	g.AddEdge('4', '1', 2);
	g.AddEdge('4', '3', -5);
	g.AddEdge('5', '4', 6);
	vector<vector<int>> vvDist;
	vector<vector<int>> vvParentPath;
	g.Floyd_Warshall(vvDist, vvParentPath);
	// ��ӡ��������֮������·��
	for (size_t i = 0; i < strlen(str); ++i)
	{
		g.PrinrtShotPath(str[i], vvDist[i], vvParentPath[i]);
		cout << endl;
	}
}

int main() {
	/*
	char arr[] = { 'a','b','c' };
	link_table::Graph<char, int, INT_MAX, true> gra(arr, sizeof(arr) / sizeof(arr[0]));
	gra.AddEdge('a', 'b', 5);
	gra.AddEdge('a', 'c', 4);
	gra.AddEdge('c', 'b', 3);
	gra.Print();
	*/

	/*
	char arr[] = { 'a','b','c','d','e','f'};
	matrix::Graph<char, int, INT_MAX, false> gra(arr, sizeof(arr) / sizeof(arr[0]));
	gra.AddEdge('a', 'b', 5);
	gra.AddEdge('a', 'c', 4);
	gra.AddEdge('c', 'b', 3);
	gra.AddEdge('c', 'f', 6);
	gra.AddEdge('e', 'b', 3);
	gra.AddEdge('e', 'f', 8);
	gra.AddEdge('a', 'd', 3);
	gra.Print();
	gra.BFS('a');
	cout << endl;
	gra.DFS('a');

	matrix::Graph<char, int, INT_MAX, false> minTree;
	int target = gra.Kruskal(minTree);

	cout << endl;
	//minTree.Print();

	matrix::Graph<char, int, INT_MAX, false> minTrees;
	target = gra.Prim(minTrees,'a');

	cout << endl;
	*/

	//TestGraphDijkstra();
	//TestGraphBellmanFord();
	TestFloydWarShall();
}
