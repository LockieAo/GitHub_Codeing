/*
图：

分类：无向图、有向图

无向图存储结构：邻接矩阵

有向图存储结构：邻接矩阵，邻接表（入边表，出边表）

图的遍历方式：深度优先（DFS）广度优先（BFS）

最小生成树：Kruskal算法 Prim算法

最短路径：

单源最短路径：无负权 Dijkstra算法

单源最短路径：有负权 Bellman-Ford算法

多源最短路径：Floyd-Warshall算法


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

//邻接表
namespace link_table {
	//邻接表结点（出边表）
	template<typename W>
	struct EdgeOut {
		int _desti;//目标结点下标
		W _weight;//权值
		EdgeOut<W>* _next;//指向下一个结点的指针

		EdgeOut(int desti, const W& weight)
			:_desti(desti)
			, _weight(weight)
			, _next(nullptr)
		{}
	};

	//邻接表结点（入边表）
	template<typename W>
	struct EdgeIn {
		int _srcti;//源结点下标
		W _weight;//权值
		EdgeIn<W>* _next;//指向下一个结点的指针

		EdgeIn(int _srcti, const W& weight)
			:_srcti(_srcti)
			, _weight(weight)
			, _next(nullptr)
		{}
	};

	//模板参数：V（顶点类型）W（权值类型）MAX_W（权值的默认值）Direction（表示是否是有向图，默认是无向图）
	template<typename V, typename W, W MAX_W = INT_MAX, bool Direction = false>
	class Graph {
		typedef EdgeOut<W> EdgeOut;
		typedef EdgeIn<W> EdgeIn;
	private:
		//用一维数组存储顶点
		vector<V> _vertex;

		//用哈希表存储顶点和下标的映射
		unordered_map<V, int> _indexMap;
		
		//使用数组存储邻接表 出边表
		vector<EdgeOut*> _outTables;

		//入边表
		vector<EdgeIn*> _inTables;
	public:
		//禁用默认构造
		Graph() = default;

		//自定义构造图
		Graph(const V* a, size_t n) {
			//存储顶点和映射
			//_vertex.reserve(n);
			for (int i = 0; i < n; i++) {
				_vertex.push_back(a[i]);
				_indexMap[a[i]] = i;
			}

			//初始化邻接表
			_outTables.resize(n,nullptr);
			_inTables.resize(n,nullptr);
		}

		//获取顶点对应的下标
		size_t GetVertexIndex(const V& value) {
			auto it = _indexMap.find(value);

			if (it == _indexMap.end()) {
				cout << value << " 顶点不存在" << endl;
				return -1;
			}
			else {
				return it->second;
			}

			return -1;
		}

		//给邻接表中添加边
		void _AddEdge(size_t srci, size_t desti, const W& weight) {

			//更新出边表
			EdgeOut*edgeOut = new EdgeOut(desti,weight);
			edgeOut->_next = _outTables[srci];
			_outTables[srci] = edgeOut;

			//更新入边表
			EdgeIn* edgeIn = new EdgeIn(srci, weight);
			edgeIn->_next = _inTables[desti];
			_inTables[desti] = edgeIn;

			//如果是无向图，双方都需要更新
			if (Direction == false) {
				//更新出边表
				EdgeOut* egOut = new EdgeOut(srci,weight);
				egOut->_next = _outTables[desti];
				_outTables[desti] = egOut;

				//更新入边表
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



		//打印
		void Print() {
			//顶点
			for (int i = 0; i < _vertex.size(); i++) {
				cout << _vertex[i] << " ";
			}
			cout << endl << endl;

			//顶点下标
			cout << "  ";
			for (int i = 0; i < _vertex.size(); i++) {
				printf("%4d", i);
			}
			cout << endl << endl;

			//邻接表 出边表
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

			//邻接表 入边表
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


//邻接矩阵
namespace matrix {
	//模板参数：V（顶点类型）W（权值类型）MAX_W（权值的默认值）Direction（表示是否是有向图，默认是无向图）
	template<typename V, typename W, W MAX_W = INT_MAX, bool Direction = false>
	class Graph {
		typedef Graph<V, W, MAX_W, Direction> Self;
	private:
		//用一维数组存储顶点
		vector<V> _vertex;

		//用哈希表存储顶点和下标的映射
		unordered_map<V, int> _indexMap;

		//用二维数组存储邻接矩阵
		vector<vector<W>> _matrix;
	public:
		//禁用默认构造
		Graph() = default;

		//自定义构造图
		Graph(const V* a, size_t n) {
			//存储顶点和映射
			//_vertex.reserve(n);
			for (int i = 0; i < n; i++) {
				_vertex.push_back(a[i]);
				_indexMap[a[i]] = i;
			}

			//初始化邻接矩阵
			_matrix.resize(n);
			for (int i = 0; i < n; i++) {
				_matrix[i].resize(n, MAX_W);
			}

			//是否需要把自身到自身的距离更新为0
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

		//获取顶点对应的下标
		size_t GetVertexIndex(const V& value) {
			auto it = _indexMap.find(value);

			if (it == _indexMap.end()) {
				cout << value << "顶点不存在" << endl;
				return -1;
			}
			else {
				return it->second;
			}

			return -1;
		}

		//给图中添加边
		void _AddEdge(size_t srci, size_t desti, const W& weight) {
			_matrix[srci][desti] = weight;

			//如果是无向图，双方都需要更新
			if (Direction == false) {
				_matrix[desti][srci] = weight;
			}
		}

		void AddEdge(const V& sour, const V& dest, const W& weight) {
			size_t srci = GetVertexIndex(sour);
			size_t desti = GetVertexIndex(dest);

			_AddEdge(srci, desti, weight);
		}


		//从某一点开始广度遍历
		void BFS(const V& sour) {
			//获取该点的下标
			int souri = GetVertexIndex(sour);

			//标记数组，用来标记该结点是否遍历过
			vector<bool> flag(_vertex.size(),false);

			//队列，用来存储即将遍历的结点
			queue<int> q;

			//将开始结点放入队列
			q.push(souri);

			while (!q.empty()) {
				int size = q.size();

				while (size--) {
					//获取队头结点
					int index = q.front();
					q.pop();
					cout << _vertex[index] << " ";
					
					//获取该结点相连且没有被遍历的结点
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
		
		//从某一点开始深度遍历
		void DFS(const V& sour) {
			int souri = GetVertexIndex(sour);

			//标记数组
			vector<bool> flag(_vertex.size(),false);

			_DFS(souri,flag);
		}
		

		//在类中定义边类，该类存储两结点及权值
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

		//最小生成树 Kruskal算法 无向图
		W Kruskal(Self& minTree) {
			size_t n = _vertex.size();

			minTree._indexMap = _indexMap;
			minTree._matrix = _matrix;
			minTree._vertex = _vertex;

			//重置邻接矩阵
			for (int i = 0; i < n; i++) {
				minTree._matrix[i].resize(n,MAX_W);
			}

			//创建最小堆
			priority_queue<Edge, vector<Edge>, greater<Edge>> minque;

			//将边存入最小堆
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					//由于是无向图，因此只需要看一半
					if (i < j && _matrix[i][j] != MAX_W) {
						minque.push(Edge(i,j,_matrix[i][j]));
					}
				}
			}

			//定义并查集
			UnionFindSet<int> ufs(n,-1);

			//n个顶点，最小生成树n-1条边,size记录找到的符合要求的边的数目
			int size = 0;

			//存储最小生成树权值
			W target = W();

			while (!minque.empty()) {
				Edge eg = minque.top();
				minque.pop();

				//先判断这条边两个顶点是否在同一个集合
				if (!ufs.Inset(eg._souri,eg._desti)) {
					//不在同一个集合
					//cout <<"节点信息：" << _vertex[eg._souri]<< " "<<_vertex[eg._desti] << " " << eg._weight << endl;
					minTree._AddEdge(eg._souri, eg._desti,eg._weight);
					ufs.Union(eg._souri, eg._desti);
					size++;
					target += eg._weight;
				}
				else {
					//在同一个集合
				}
			}

			if (size == n - 1) {
				//cout << target << endl;
				return target;
			}

			return W();

		}

		//最小生成树 Prim算法 无向图
		W Prim(Self& minTree,const W& sour) {
			//获取开始结点下标
			size_t souri = GetVertexIndex(sour);

			size_t n = _vertex.size();
			minTree._indexMap = _indexMap;
			minTree._matrix = _matrix;
			minTree._vertex = _vertex;

			//重置邻接矩阵
			for (int i = 0; i < n; i++) {
				minTree._matrix[i].resize(n, MAX_W);
			}

			//标记数组
			//X标记该结点是不是已经被选择，被选择则为true
			vector<bool> X(n,false);

			//Y标记该结点是不是还没有被选择，没有被选择则为false
			vector<bool> Y(n,true);

			X[souri] = true;
			Y[souri] = false;

			//创建最小堆
			priority_queue<Edge,vector<Edge>,greater<Edge>> minque;

			//选出与开始结点相连的最小边，首先把与开始结点相连的所有边添加进入最小堆
			for (int i = 0; i < n; i++) {
				if (_matrix[souri][i] != MAX_W) {
					minque.push(Edge(souri, i, _matrix[souri][i]));
				}
			}

			//选择边，size保存已经选出的边的个数
			int size = 0;
			W target = W();

			while (!minque.empty()) {
				Edge eg = minque.top();
				minque.pop();

				if (X[eg._desti]) {
					//这条边的目标结点已经被选择，不能再选了
				}
				else {
					//这条边的目标结点没有被选择

					minTree._AddEdge(eg._souri, eg._desti, eg._weight);
					cout << "节点信息：" << _vertex[eg._souri] << " " << _vertex[eg._desti] << " " << eg._weight << endl;
					target += eg._weight;

					//该结点已选择，进行标记
					X[eg._desti] = true;

					Y[eg._desti] = false;

					size++;

					if (size == n - 1) {
						break;
					}

					//把与该目标结点相连的所有没有被选择的边全部添加进入最小堆
					for (int i = 0; i < n; i++) {
						//当该边存在，且目标结点并没有被选择过
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

		//单源最短路径：无负权 Dijkstra算法
		//sour：源结点 destWieght：源节点到各个结点的目前的最短路径 pPath：保存当前下标的结点的父节点
		void Dijkstra(const V& sour, vector<W>& destWieght, vector<int>& pPath) {
			//获取源节点下标
			size_t souri = GetVertexIndex(sour);

			//获取结点个数
			size_t n = _vertex.size();

			//初始化数组
			destWieght.resize(n,MAX_W);
			pPath.resize(n,-1);

			//源节点到自己的路径是0
			destWieght[souri] = 0;
			pPath[souri] = souri;

			//S标记该结点是否找到最短路径
			vector<bool> S(n,false);

			//每轮选出一个最短路径，选n轮
			for (int i = 0; i < n; i++) {
				//选择一个当前还没有找到最短路径，且距离源节点路径最短的结点
				//u用来保存寻找到的结点下标
				int u = 0;
				//min保存对应权值
				W min = MAX_W;
				for (int j = 0; j < n; j++) {
					if (S[j] == false && destWieght[j] < min) {
						u = j;
						min = destWieght[j];
					}
				}

				//找到离源节点最近的了
				S[u] = true;
				//进行松弛操作，把当前还没有找到最短路径的结点到源节点的最短距离进行更新
				for (int v = 0; v < n; v++) {
					if (S[v] == false && _matrix[u][v] != MAX_W && (destWieght[u] + _matrix[u][v]) < destWieght[v]) {
						destWieght[v] = destWieght[u] + _matrix[u][v];
						pPath[v] = u;
					}
				}

			}

		}

		//单源最短路径：Bellman-Ford算法，带负权
		bool Bellman_Ford(const V& sour, vector<W>& destWieght, vector<int>& pPath) {
			//获取源节点下标
			size_t souri = GetVertexIndex(sour);

			//获取结点个数
			size_t n = _vertex.size();

			//初始化数组
			destWieght.resize(n, MAX_W);
			pPath.resize(n, -1);


			destWieght[souri] = W();

			//如果当前轮修改了最短路径，可能会影响其他结点最短路径，因此需要下一轮进行更正。
			//最多更正n轮，因为只有n个结点，当第n轮更正结束后，会进行负权回路判断。
			for (int k = 0; k < n;k++) {
				//用来标记本轮是否更新
				bool update = false;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {

						if (_matrix[i][j] != MAX_W && (destWieght[i] + _matrix[i][j]) < destWieght[j]) {
							destWieght[j] = destWieght[i] + _matrix[i][j];
							pPath[j] = i;
							//更新标志
							update = true;
						}
					}
				}

				if (update == false) {
					break;
				}
			}

			//判断是否有负权回路，也就是判断是否还可以更新
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {

					if (_matrix[i][j] != MAX_W && (destWieght[i] + _matrix[i][j]) < destWieght[j]) {
						return false;
					}
				}
			}

			return true;
		}

		//多源最短路径：Floyd-Warshall算法
		//vvDestWeight：从i到j的权值 vvpPath：从i到j的最短路径中j的前一个结点下标
		void Floyd_Warshall(vector<vector<W>>& vvDestWeight, vector<vector<int>>& vvpPath) {
			//获取结点个数
			size_t n = _vertex.size();

			//修改矩阵元素个数
			vvDestWeight.resize(n);
			vvpPath.resize(n);

			//初始化矩阵
			for (int i = 0; i < n; i++) {
				vvDestWeight[i].resize(n,MAX_W);
				vvpPath[i].resize(n,-1);
			}

			//给矩阵赋值
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					//当从i到j是直接相连的
					if (_matrix[i][j] != MAX_W) {
						//获取从i到j的权值
						vvDestWeight[i][j] = _matrix[i][j];
						//从i到j直接联通，因此j的前一个结点下标是i
						vvpPath[i][j] = i;
					}
					//如果是同一个节点，把权值更新为默认值
					if (i == j) {
						vvDestWeight[i][j] = W();
					}
				}
			}

			//进行最短路径计算
			//k是中间结点
			for (int k = 0; k < n; k++) {
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						//如果从i到k有路径 从k到j有路径 且从i到k到j的权值比原先从i到j短，进行更新
						if (vvDestWeight[i][k] != MAX_W && vvDestWeight[k][j] != MAX_W && (vvDestWeight[i][k] + vvDestWeight[k][j]) < vvDestWeight[i][j]) {
							vvDestWeight[i][j] = vvDestWeight[i][k] + vvDestWeight[k][j];
							vvpPath[i][j] = vvpPath[k][j];
						}
					}
				}
			}
		}
		
		//打印最短路径
		void PrinrtShotPath(const V& sour, const vector<W>& destWieght, const vector<int>& pPath) {
			size_t souri = GetVertexIndex(sour);
			size_t n = destWieght.size();

			for (int i = 0; i < n; i++) {
				if (i != souri) {
					//存储源节点到该结点路径
					vector<int> path;
					//存储该结点所在路径的上一个结点
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

					cout << "此路径权值和：" << destWieght[i]<<endl;
				}
			}
		}


		//打印
		void Print() {
			//顶点
			for (int i = 0; i < _vertex.size(); i++) {
				cout << _vertex[i] << " ";
			}
			cout << endl << endl;

			//顶点下标
			cout << "  ";
			for (int i = 0; i < _vertex.size(); i++) {
				printf("%4d", i);
			}
			cout << endl << endl;
			//邻接矩阵
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

			//打印源点->目的点（权值）
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
		cout << "存在负权回路" << endl;
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
	// 打印任意两点之间的最短路径
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

