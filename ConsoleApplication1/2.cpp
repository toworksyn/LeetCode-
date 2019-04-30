#include"head.h"
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
bool isValidBST(TreeNode* root) {
	int front;
	TreeNode* temp(root);
	stack<TreeNode*> st;
	bool first(true);
	while (!st.empty() || temp) {
		while (temp) {
			st.push(temp);
			temp = temp->left;
		}
		if (first) {
			front = st.top()->val;
			first = false;
		}
		else if (st.top()->val <= front)
			return false;
		front = st.top()->val;
		temp = st.top()->right;
		st.pop();
	}
	return true;
}
vector<int> Mid(TreeNode* root) {
	TreeNode* temp(root);
	vector<int> nodes;
	stack<TreeNode*> st;
	while (!st.empty() || temp) {
		while (temp) {
			st.push(temp);
			temp = temp->left;
		}
		nodes.push_back(st.top()->val);
		temp = st.top()->right;
		st.pop();
	}
	return nodes;
}
vector<int> Front(TreeNode* root) {
	TreeNode* temp(root);
	vector<int> nodes;
	stack<TreeNode*> st;
	while (!st.empty() || temp) {
		while (temp) {
			nodes.push_back(temp->val);
			st.push(temp);
			temp = temp->left;
		}
		temp = st.top()->right;
		st.pop();
	}
	return nodes;
}
TreeNode* find_prt(TreeNode* root, int num) {
	TreeNode* prt(nullptr);
	TreeNode* res(root);
	while (res) {
		if (res->val == num)
			return prt;
		prt = res;
		if (res->val < num)
			res = res->right;
		else
			res = res->left;
	}
}
void recoverTree(TreeNode* root) {
	TreeNode* temp(root);
	vector<TreeNode*> nodes;
	stack<TreeNode*> st;
	while (!st.empty() || temp) {
		while (temp) {
			st.push(temp);
			temp = temp->left;
		}
		nodes.push_back(st.top());
		temp = st.top()->right;
		st.pop();
	}
	TreeNode* hot1, *hot2;
	int i(0), j(nodes.size() - 1);
	while (i != nodes.size()) {
		if (nodes[i]->val > nodes[i + 1]->val) {
			hot1 = nodes[i];
			break;
		}
		++i;
	}
	while (j != i) {
		if (nodes[j]->val < nodes[j - 1]->val) {
			hot2 = nodes[j];
			break;
		}
		--j;
	}
	int num(hot1->val);
	hot1->val = hot2->val;
	hot2->val = num;
}
void roll(TreeNode* left, TreeNode* right) {
	TreeNode* temp(left);
	left = right;
	right = temp;
}
void Roll(TreeNode* root) {
	TreeNode* temp(root);
	while (temp) {
		roll(temp->left, temp->right);
		Roll(temp->left);
		Roll(temp->right);
	}
}
bool isSameTree(TreeNode* p, TreeNode* q) {
	if (!p && !q)
		return true;
	else if ((!p && q) || (p && !q))
		return false;
	else if (p->val != q->val)
		return false;
	else
		return(isSameTree(p->left, q->left) &&
			isSameTree(p->right, q->right));
}
bool compRoot(TreeNode* lroot, TreeNode* rroot) {
	if (!lroot) return (NULL == rroot);
	if (NULL == rroot) return false;
	if (lroot->val != rroot->val) return false;
	return (compRoot(lroot->left, rroot->right) && compRoot(lroot->right, rroot->left));
}
vector<vector<int>> levelOrder(TreeNode* root) {
	vector<vector<int>> res;
	int floor(0);
	stack<TreeNode*> st1, st2;
	TreeNode* temp(root);
	st1.push(temp);
	while (temp) {
		res.push_back({});
		if (!st1.empty()) {
			while (!st1.empty()) {
				temp = st1.top();
				res[floor].push_back(temp->val);
				if (st1.top()->right)
					st2.push(st1.top()->right);
				if (st1.top()->left)
					st2.push(st1.top()->left);
				st1.pop();
			}
			temp = st2.top();
		}
		else if (!st2.empty()) {
			while (!st2.empty()) {
				temp = st2.top();
				res[floor].push_back(temp->val);
				if (st2.top()->left)
					st1.push(st2.top()->left);
				if (st2.top()->right)
					st1.push(st2.top()->right);
				st2.pop();
			}
			temp = st1.top();
		}
		else
			break;
		++floor;
	}
	return res;
}
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
	vector<vector<int>> res;
	int floor(0);
	stack<TreeNode*> st1, st2;
	TreeNode* temp(root);
	st1.push(temp);
	while (temp) {
		res.push_back({});
		if (!st1.empty()) {
			while (!st1.empty()) {
				temp = st1.top();
				res[floor].push_back(temp->val);
				if (st1.top()->left)
					st2.push(st1.top()->left);
				if (st1.top()->right)
					st2.push(st1.top()->right);
				st1.pop();
			}
		}
		else if (!st2.empty()) {
			while (!st2.empty()) {
				temp = st2.top();
				res[floor].push_back(temp->val);
				if (st2.top()->right)
					st1.push(st2.top()->right);
				if (st2.top()->left)
					st1.push(st2.top()->left);
				st2.pop();
			}
		}
		else
			break;
		++floor;
	}
	res.pop_back();
	return res;
}
void DFS(TreeNode* root, int roof, int& max) {
	if (root) {
		DFS(root->left, roof + 1, max);
		DFS(root->right, roof + 1, max);
	}
	if (roof > max)
		max = roof;
}
int maxDepth(TreeNode* root) {
	int res(0);
	DFS(root, 0, res);
	return res;
}
TreeNode* buildTree2(vector<int>& preorder, vector<int>& inorder) {
	int len = preorder.size(), loc;
	if (len == 0)
		return nullptr;
	int mid = preorder[0];
	TreeNode* res = new TreeNode(mid);
	for (loc = 0; loc != inorder.size(); ++loc) {
		if (inorder[loc] == mid)
			break;
	}
	vector<int> lf_pre(loc), lf_in(loc), rt_pre(len - loc - 1), rt_in(len - loc - 1);
	copy(preorder.begin() + 1, preorder.begin() + loc + 1, lf_pre.begin());
	copy(inorder.begin(), inorder.begin() + loc, lf_in.begin());
	copy(preorder.begin() + loc + 1, preorder.end(), rt_pre.begin());
	copy(inorder.begin() + loc + 1, inorder.end(), rt_in.begin());
	res->left = buildTree2(lf_pre, lf_in);
	res->right = buildTree2(rt_pre, rt_in);
	return res;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
	int len = postorder.size(), loc;
	if (len == 0)
		return nullptr;
	int mid = postorder[len - 1];
	TreeNode* res = new TreeNode(mid);
	for (loc = 0; loc != inorder.size(); ++loc) {
		if (inorder[loc] == mid)
			break;
	}
	vector<int> lf_pos(loc), lf_in(loc), rt_pos(len - loc - 1), rt_in(len - loc - 1);
	copy(postorder.begin(), postorder.begin() + loc, lf_pos.begin());
	copy(inorder.begin(), inorder.begin() + loc, lf_in.begin());
	copy(postorder.begin() + loc, postorder.end() - 1, rt_pos.begin());
	copy(inorder.begin() + loc + 1, inorder.end(), rt_in.begin());
	res->left = buildTree(lf_in, lf_pos);
	res->right = buildTree(rt_in, rt_pos);
	return res;
}
vector<vector<int>> levelOrder2(TreeNode* root) {
	vector<vector<int>> res;
	int floor(0);
	stack<TreeNode*> st1, st2;
	TreeNode* temp(root);
	st1.push(temp);
	while (temp) {
		res.push_back({});
		if (!st1.empty()) {
			while (!st1.empty()) {
				temp = st1.top();
				res[floor].push_back(temp->val);
				if (st1.top()->right)
					st2.push(st1.top()->right);
				if (st1.top()->left)
					st2.push(st1.top()->left);
				st1.pop();
			}
		}
		else if (!st2.empty()) {
			while (!st2.empty()) {
				temp = st2.top();
				res[floor].push_back(temp->val);
				if (st2.top()->left)
					st1.push(st2.top()->left);
				if (st2.top()->right)
					st1.push(st2.top()->right);
				st2.pop();
			}
		}
		else
			break;
		++floor;
	}
	res.pop_back();
	return vector<vector<int>> (res.rbegin(), res.rend());
}
TreeNode* HelpConstruct(vector<int>& nums, int head, int len) {
	if (len <= 0)
		return nullptr;
	int mid = head + (len - 1) / 2;
	TreeNode* root = new TreeNode(nums[mid]);
	root->left = HelpConstruct(nums, head, mid - head);
	root->right = HelpConstruct(nums, mid + 1, len - mid + head - 1);
	return root;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
	if (nums.empty())
		return nullptr;
	int len = nums.size();
	int mid = (len - 1) / 2;
	TreeNode* root = new TreeNode(nums[mid]);
	root->left = HelpConstruct(nums, 0, mid);
	root->right = HelpConstruct(nums, mid + 1, len - mid - 1);
	return root;
}
void DFS2(TreeNode* root, int roof, int& min) {
	if (root) {
		if(root->left)
			DFS2(root->left, roof + 1, min);
		if (root->right)
			DFS2(root->right, roof + 1, min);
	}
	if (!root->left && !root->right && roof < min)
		min = roof;
}
int minDepth(TreeNode* root) {
	int res(INT_MAX);
	DFS2(root, 1, res);
	return res;
}
bool hasPathSum(TreeNode* root, int sum) {
	if (!root)	return false;
	stack<TreeNode*> st;
	st.push(root);
	int res(0);
	while (!st.empty()) {
		TreeNode* temp = st.top();
		res += temp->val;
		st.pop();
		if (temp->right)
			st.push(temp->right);
		if (temp->left)
			st.push(temp->left);
		if (!temp->right && !temp->left) {
			if (res == sum)
				return true;
			res -= temp->val;
		}
	}
	return false;
}
TreeNode* CreatTree(vector<int> nums) {
	queue<TreeNode*> qe;
	TreeNode* root = new TreeNode(nums[0]);
	qe.push(root);
	int len = nums.size(), loc(1), num = qe.size();
	while (loc != len && !qe.empty()) {
		num = qe.size();
		while (num != 0) {
			TreeNode* temp = qe.front();
			if (loc != len) {
				if (nums[loc] != -1) {
					temp->left = new TreeNode(nums[loc++]);
					qe.push(temp->left);
				}
				else {
					temp->left = nullptr;
					++loc;
				}
			}
			if (loc != len) {
				if (nums[loc] != -1) {
					temp->right = new TreeNode(nums[loc++]);
					qe.push(temp->right);
				}
				else {
					temp->right = nullptr;
					++loc;
				}
			}
			qe.pop();
			--num;
		}
	}
	return root;
}
void Help(vector<vector<int>>& res, vector<int>& temp, 
	TreeNode* root, int sum) {
	temp.push_back(root->val);
	if (root->left == nullptr && root->right == nullptr
		&& root->val == sum) {
		res.push_back(temp);
		temp.pop_back();
		return;
	}
	if(root->left)
		Help(res, temp, root->left, sum - root->val);
	if (root->right)
		Help(res, temp, root->right, sum - root->val);
		temp.pop_back();
}
vector<vector<int>> pathSum(TreeNode* root, int sum) {
	vector<int> temp;
	vector<vector<int>> res;
	Help(res, temp, root, sum);
	return res;
}
void flatten(TreeNode* root) {
	TreeNode* temp(root);
	stack<TreeNode*> st;
	vector<TreeNode*> vc;
	while (!st.empty() || temp) {
		while (temp) {
			vc.push_back(temp);
			st.push(temp);
			temp = temp->left;
		}
		temp = st.top()->right;
		st.pop();
	}
	for (int i(1); i != vc.size(); ++i) {
		vc[i - 1]->left = nullptr;
		vc[i - 1]->right = vc[i];
	}
}
void Exist(string s, string t, int loc, int num, int& res) {
	int newloc(-1);
	for (int i = loc + 1; i != s.size(); ++i) {
		if (s[i] == t[num]) {
			newloc = i;
			if (num == t.size() - 1)
				++res;
			else
				Exist(s, t, newloc, num + 1, res);
		}
	}
}
int numDistinct(string s, string t) {
	int slen = s.size(), tlen = t.size();
	if (tlen > slen)	return 0;
	if (tlen == 0)	return 1;
	int res(0);
	if (tlen == 1) {
		for (int i = 0; i != slen; ++i)
			if (s[i] == t[0])
				++res;
	}
	else {
		char head = t[0];
		for (int i(0); i != slen; ++i) {
			if (s[i] == head)
				Exist(s, t, i, 1, res);
		}
	}
	return res;
}
struct TreeLinkNode {
	TreeLinkNode *left;
	TreeLinkNode *right;
	TreeLinkNode *next;
};
void connect(TreeLinkNode *root) {
	if (!root) return;
	TreeLinkNode *start = root, *cur = NULL;
	while (start->left) {
		cur = start;
		while (cur) {
			cur->left->next = cur->right;
			if (cur->next) cur->right->next = cur->next->left;
			cur = cur->next;
		}
		start = start->left;
	}
}
void TriPath(vector<vector<int>>& triangle, int roof,
	int loc, int temp,int &res) {
	if (roof == triangle.size()) {
		if (temp < res)
			res = temp;
		return;
	}
	while (loc != triangle[roof].size()) {
		TriPath(triangle, roof + 1, loc, temp + triangle[roof][loc], res);
		TriPath(triangle, roof + 1, loc + 1, temp + triangle[roof][loc + 1], res);
		temp -= triangle[roof][loc];
		++loc;
	}
}
int minimumTotal(vector<vector<int>>& triangle) {
	int res = INT_MAX;
	TriPath(triangle, 0, 0, 0, res);
	return res;
}
int maxProfit0(vector<int>& prices) {
	int len = prices.size();
	if (len < 2)
		return 0;
	int left(-1);
	for (int i = 0; i != len - 1; ++i) {
		if (prices[i] < prices[i + 1]) {
			left = i;
			break;
		}
	}
	if (left == -1)
		return 0;
	int res = 0;
	for (int right = left + 1; right != len; ++right) {
		if (prices[right] - prices[left] > res)
			res = prices[right] - prices[left];
		if (prices[right] < prices[left])
			left = right;
	}
	return res;
}
int maxProfit1(vector<int>& prices) {
	int len = prices.size();
	if (len < 2)
		return 0;
	int left(-1);
	for (int i = 0; i != len - 1; ++i) {
		if (prices[i] < prices[i + 1]) {
			left = i;
			break;
		}
	}
	if (left == -1)
		return 0;
	int res = 0;
	for (int right = left + 1; right != len; ++right) {
		if (prices[right] < prices[right - 1]) {
			res += prices[right - 1] - prices[left];
			left = right;
		}
	}
	if (prices[len - 1] > prices[len - 2])
		res += prices[len - 1] - prices[left];
	return res;
}
int maxProfit(vector<int>& prices) {
	int len = prices.size();
	if (len < 4)
		return maxProfit0(prices);
	vector<int> temp1{};
	vector<int> temp2 = prices;
	int res(0);
	while (!temp2.empty()) {
		if (maxProfit0(temp1) + maxProfit0(temp2) > res)
			res = maxProfit0(temp1) + maxProfit0(temp2);
		temp1.push_back(temp2[0]);
		temp2.erase(temp2.begin());
	}
	return res;
}
bool isPalindrome(string s) {
	int len = s.size();
	if (len < 2)
		return true;
	for (int i = 0; i != len; ++i) {
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	}
	int left(-1), right(len);
	while (true) {
		for (int i = left + 1; i != len; ++i) {
			left = i;
			if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')
				|| (s[i] >= '0' && s[i] <= '9')) {
				break;
			}
		}
		for (int j = right - 1; j != -1; --j) {
			right = j;
			if ((s[j] >= 'A' && s[j] <= 'Z') || (s[j] >= 'a' && s[j] <= 'z')
				|| (s[j] >= '0' && s[j] <= '9')) {
				break;
			}
		}
		if (left >= right)
			break;
		if (s[left] != s[right])
			return false;
	}
	return true;
}
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
	int len = wordList.size();
	int i(0), j(0), begin_loc(0);
	while (i != len) {
		if (endWord == wordList[i])
			break;
		if ((wordList[i] == beginWord) && j == 0) {
			j = 1;
			begin_loc = i;
		}
		++i;
	}
	if (i == len)	return false;
	if (beginWord == endWord)	return 1;
	while (i != len) {
		if ((wordList[i] == beginWord) && j == 0) {
			j = 1;
			begin_loc = i;
		}
		++i;
	}
	if (j == 0) {
		wordList.insert(wordList.begin(), beginWord);
		++len;
	}

	int word_len = wordList[0].size();
	vector<vector<bool>> flag(len, vector<bool>(len, false));
	for (int m = 0; m != len; ++m) {
		int num(0);
		for (int n = m; n != len; ++n) {
			for (int loc(0); loc != word_len; ++loc) {
				if (wordList[m][loc] != wordList[n][loc])
					++num;
			}
			if (num == 1)
				flag[m][n] = flag[n][m] = true;
			num = 0;
		}
	}
	for (int i = 0; i != len; ++i) {
		for (int j = 0; j != len; ++j) {
			cout << flag[i][j] << " ";
		}
		cout << endl;
	}
	queue<int> path;
	int res(1);
	path.push(begin_loc);
	int qlen = path.size();
	while (qlen && res <= len) {
		++res;
		while (qlen != 0) {
			int temp = path.front();
			path.pop();
			for (int i = 0; i != len; ++i) {
				if (flag[temp][i]) {
					if (wordList[i] == endWord)
						return res;
					else
						path.push(i);
				}
			}
			--qlen;
		}
		qlen = path.size();
	}
	return 0;
}
int longestConsecutive(vector<int>& nums) {
	if (nums.empty())	return 0;
	set<int> help_nums;
	for (int temp : nums) {
		help_nums.insert(temp);
	}
	int res = 1;
	auto loc = help_nums.begin();
	int left = *loc, right, temp = 1;
	while (++loc != help_nums.end()) {
		right = *loc;
		if (right == left + 1)
			++temp;
		else {
			res = max(res, temp);
			temp = 1;
		}
		left = right;
	}
	res = max(res, temp);
	return res;
}
void DFS3(TreeNode* root, int& res, int sum) {
	sum = 10 * sum + root->val;
	if(root->left)
		DFS3(root->left, res, sum);
	if(root->right)
		DFS3(root->right, res, sum);
	if(!(root->left)&&!(root->right))
		res += sum;
}
int sumNumbers(TreeNode* root) {
	if (!root)	return 0;
	int res(0), temp(0);
	DFS3(root, res, temp);
	return res;
}
void findO(pair<int,int> loc, vector<vector<char>>& board) {
	queue<pair<int, int>> qe;
	qe.push(loc);
	while (!qe.empty()) {
		unsigned int row = qe.front().first, col = qe.front().second;
		qe.pop();
		board[row][col] = 'c';
		if (row - 1 >= 0 && board[row - 1][col] == 'O')
			qe.push({ row - 1, col });
		if (col - 1 >= 0 && board[row][col - 1] == 'O')
			qe.push({ row, col - 1 });
		if (row + 1 < board.size() && board[row + 1][col] == 'O')
			qe.push({ row + 1, col });
		if (col + 1 < board[0].size() && board[row][col + 1] == 'O')
			qe.push({ row, col + 1 });
	}
}
void findOO(pair<int, int> loc, vector<vector<char>>& board) {
	unsigned int row = loc.first, col = loc.second;
	board[row][col] = 'c';
	if (row - 1 >= 0 && board[row - 1][col] == 'O')
		findOO({ row - 1, col }, board);
	if (col - 1 >= 0 && board[row][col - 1] == 'O')
		findOO({ row, col - 1 }, board);
	if (row + 1 < board.size() && board[row + 1][col] == 'O')
		findOO({ row + 1, col }, board);
	if (col + 1 < board[0].size() && board[row][col + 1] == 'O')
		findOO({ row, col + 1 }, board);
}
void solve(vector<vector<char>>& board) {
	if (board.size() < 3)	return;
	int row = board.size(), col = board[0].size();
	if (col < 3)	return;
	for (int i = 0; i != col; ++i) {
		if (board[0][i] == 'O')
			findOO({ 0, i }, board);
		if(board[row - 1][i] == 'O')
			findOO({ row - 1, i }, board);
	}
	for (int j = 1; j != row - 1; ++j) {
		if (board[j][0] == 'O')
			findOO({ j, 0 }, board);
		if (board[j][col - 1] == 'O')
			findOO({ j, col - 1 }, board);
	}
	for (int i = 0; i != row; ++i) {
		for (int j = 0; j != col; ++j) {
			if (board[i][j] == 'c')
				board[i][j] = 'O';
			else
				board[i][j] = 'X';
		}
	}
}
bool isPali(string str) {
	for (int i = 0; i<str.length() / 2; i++) {
		if (str[i] != str[str.length() - i - 1])
			return false;
	}
	return true;
}
void Dfs(int& ans, int path, string s, int start) {
	if (start == s.length()) {
		if (path - 1 < ans)
			ans = path - 1;
		return;
	}
	for (int i = start; i<s.length(); i++) {
		if (isPali(s.substr(start, i - start + 1))) {
			Dfs(ans, path + 1, s, i + 1);
		}
	}
}
int minCut(string s) {
	int ans(INT_MAX);
	if (s.empty())
		return 0;
	int path(0);
	Dfs(ans, path, s, 0);
	return ans;
}
struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};
UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
	if (node == NULL) return NULL;
	//开辟新的空间存储copy
	UndirectedGraphNode* copy = new UndirectedGraphNode(node->label);
	//查找去重用的map  unordered_map<node, clonedNode> 放原始node和其复制品
	map<UndirectedGraphNode*, UndirectedGraphNode*> cmap;
	//存储的队列，进行BFS
	queue<UndirectedGraphNode*> graphQ;
	graphQ.push(node);               //根结点添加到队列
	cmap.insert({ node, copy });   //把根节点和其复制品放入map  

	while (!graphQ.empty()){
		UndirectedGraphNode* cur = graphQ.front();   //当前处理对象
		graphQ.pop();
		UndirectedGraphNode* curClone = cmap[cur];   //当前处理对象的复制品 因为在前面的neighbor里已经被创建

													 //对当前顶点的每一个neighbor进行判断，因为有的neighbor已经被复制，有的没有
		for (int i = 0; i < cur->neighbors.size(); i++){
			UndirectedGraphNode* neighbor = cur->neighbors[i];
			//如果之前没有拷贝过
			if (cmap.find(neighbor) == cmap.end()){
				UndirectedGraphNode* neighborClone = new UndirectedGraphNode(neighbor->label);
				curClone->neighbors.push_back(neighborClone);   //给curClone添加复制的neighbor
				cmap.insert({ neighbor, neighborClone });   //添加到map中
				graphQ.push(neighbor);   //添加到队列为了将来的遍历
			}
			else{    // 之前已经被复制过的neighbor
				UndirectedGraphNode* neighborClone = cmap[neighbor];   //从map中取出之前的copy版本
				curClone->neighbors.push_back(neighborClone);     // 给curClone添加复制的neighbor
			}
		}
	}
	return copy;
}
int Drive(int loc, vector<int>& gas, vector<int>& cost) {
	int rest = 0, loc_temp = loc, len = gas.size();
	do {
		rest += gas[loc_temp];
		rest -= cost[loc_temp];
		if (rest < 0)
			return loc_temp;
		loc_temp = (loc_temp + 1) % len;
	} while (loc_temp != loc);
	return loc_temp;
}
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
	if (gas.empty())	return 0;
	int len = gas.size(), loc = 0;
	for (int i = 0; i < len; i = loc) {
		if (gas[i] >= cost[i]) {
			loc = Drive(i, gas, cost);
			if (loc == i)
				return i;
		}
	}
	return -1;
}
int candy(vector<int>& ratings) {
	if (ratings.empty())	return 0;						//空数组返回0
	vector<int> rating{ INT_MIN };							//拷贝，并在两侧各留一空位置以方便边界运算
	rating.insert(rating.end(), ratings.begin(), ratings.end());
	rating.push_back(INT_MIN);
	int lowest = INT_MAX, len = rating.size();				//保存原数组中最小值
	map<int, vector<int>> mp;								//存储不同数字在数组中位置，每一数字可能有多个位置因此用vector保存
	for (int i = 1; i != len - 1; ++i) {
		mp[rating[i]].push_back(i);
		if (rating[i] < lowest)
			lowest = rating[i];
	}
	rating[0] = rating[len - 1] = 0;				//边界设置为0，以方便计算

	int n = 0;												//计数器
	for (map<int, vector<int>>::iterator i = mp.begin(); i != mp.end(); ++i, ++n) {	
		int num = i->second.size();							//将rating数组中各个数字设置为1,2,3...的连续形式，以方便计算
		for (int j = 0; j != num; ++j) {
			int loc = i->second[j];	
			rating[loc] = 1 + n;
		}
	}
	for (map<int, vector<int>>::iterator i = mp.begin(); i != mp.end(); ++i) {			//按从小到大顺序分别进行不同数字的计算
		int num = i->second.size();							//每一个数字的数量
		for (int j = 0; j != num; ++j) {
			int loc = i->second[j];							//对每个数字的不同位置更新
			if (rating[loc] <= rating[loc - 1] && rating[loc] <= rating[loc + 1])		//若此值不大于其两侧任意一值，则将其设置为1
				rating[loc] = 1;
			else {
				int a = (rating[loc] > rating[loc - 1]) ? rating[loc - 1] : INT_MIN;	//否则，在两侧中找出小于他的值中最大的那个值，并
				int b = (rating[loc] > rating[loc + 1]) ? rating[loc + 1] : INT_MIN;	//将其加1，赋给当前值
				rating[loc] = max(a, b) + 1;
			}
		}
	}
	int res(0);
	for (int i = 1; i != len - 1; ++i)						//将更新过值的数组累加，并每个值都加上最小值与1的差值，
		res += rating[i];									//计算之和即为结果
	return res;
}
int singleNumber0(vector<int>& nums) {
	set<int> st;
	for (int i = 0; i != nums.size(); ++i) {
		if (st.find(nums[i]) == st.end())
			st.insert(nums[i]);
		else
			st.erase(nums[i]);
	}
	return *st.begin();
}
int singleNumber1(vector<int>& nums) {
	for (int i = 1; i != nums.size(); ++i) {
		nums[0] = nums[0] ^ nums[i];
	}
	return nums[0];
}
int singleNumber(vector<int>& nums) {
	int length = nums.size();
	int result = 0;
	for (int i = 0; i != 32; ++i)
	{
		int mask = 1 << i;  //从最低位开始
		int cnt = 0;
		for (int j = 0; j != length; ++j)
		{
			if (mask & nums[j])  //统计有1的个数
				++cnt;
		}
		if (cnt % 3)  //不能整除说明在该位为1
			result |= mask;
	}
	return result;
}
struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
RandomListNode *copyRandomList(RandomListNode *head) {
	if (!head)	return nullptr;
	map<RandomListNode*, RandomListNode*> mp;
	RandomListNode *front = new RandomListNode(-1);
	RandomListNode *temp = head, *res = front;
	while (temp) {
		if (mp.find(temp) == mp.end())
			mp[temp] = new RandomListNode(temp->label);
		front->next = mp[temp];
		if (mp.find(temp->random) == mp.end())
			mp[temp->random] = ((temp->random == nullptr) ? nullptr : new RandomListNode(temp->random->label));
		mp[temp]->random = mp[temp->random];
		front = front->next;
		temp = temp->next;
	}
	return res->next;
}
bool wordBreak0(string s, vector<string>& wordDict) {
	if (s.empty())	return true;
	int len = s.size();
	int loc = 1;
	for (; loc <= len; ++loc) {
		if (find(wordDict.begin(), wordDict.end(), s.substr(0, loc)) != wordDict.end()) {
			if (wordBreak0(s.substr(loc, len), wordDict))
				return true;
		}
	}
	return false;
}
bool wordBreak(string s, vector<string>& wordDict) {
	int len = s.size();
	vector<bool> flag(len + 1, false);
	flag[0] = true;
	unordered_set<string> dict;
	for (string temp : wordDict)
		dict.insert(temp);
	for (int i = 1; i <= len; ++i) {
		for (int loc = i - 1; loc >= 0; --loc) {
			if (dict.find(s.substr(loc, i - loc)) != dict.end() && flag[loc]) {
				flag[i] = true;
				break;
			}
		}
	}
	return flag[len];
}
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
bool hasCycle(ListNode *head) {
	unordered_set<ListNode *> ust;
	while (head) {
		if (ust.find(head) == ust.end()) {
			ust.insert(head);
			head = head->next;
		}
		else return true;
	}
	return false;
}
ListNode *detectCycle(ListNode *head) {
	if (!head)
		return head;
	ListNode *slow = head;
	ListNode *fast = head->next;
	bool flag = true;
	while (flag && fast && fast->next && fast->next->next) {
		if (slow == fast) 
			flag = false;
		if (fast == nullptr) {
			flag = true;
			break;
		}
		slow = slow->next;
		fast = fast->next->next;
	}
	if (flag)
		return nullptr;
	fast = head;
	while (fast != slow) {
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}
void reorderList(ListNode *head)
{
	if (head == NULL || head->next == NULL)
		return;
	//分成两段
	ListNode *preSlow = NULL;
	ListNode *slow = head, *fast = head;
	while (fast&&fast->next)
	{
		preSlow = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	preSlow->next = NULL; //前半段

						  //反转后半段
	ListNode *newBeg = slow;
	ListNode *last = newBeg->next;
	while (last)
	{
		ListNode *temp = last->next;
		last->next = newBeg;
		newBeg = last;
		last = temp;
	}
	slow->next = NULL;

	//合并
	fast = head;
	preSlow = NULL;
	while (fast) //注：以前半段为条件
	{
		ListNode *tem = newBeg->next;
		newBeg->next = fast->next;
		fast->next = newBeg;
		fast = newBeg->next;
		preSlow = newBeg;
		newBeg = tem;
	}
	if (newBeg != NULL)   //因节点个数为奇数时，后段比前段多一个，所以最后要判断
		preSlow->next = newBeg;
}
vector<int> preorderTraversal(TreeNode* root) {
	stack<TreeNode*> st;
	vector<int> res;
	TreeNode* temp(root);
	while (temp || !st.empty()) {
		while (temp) {
			res.push_back(temp->val);
			st.push(temp);
			temp = temp->left;
		}
		if (!st.empty()) {
			temp = st.top();
			st.pop();
			temp = temp->right;
		}
	}
	return res;
}
vector<int> postorderTraversal(TreeNode* root) {
	stack<TreeNode*> st;
	vector<int> res;
	TreeNode* temp(root);
	map<TreeNode*, int> flag;
	while (temp || !st.empty()) {
		while (temp) {
			st.push(temp);
			temp = temp->left;
		}
		if (!st.empty()) {
			if (flag.find(st.top()) == flag.end()) {
				flag[st.top()] = 0;
				temp = st.top()->right;
			}
			else if(flag[st.top()] == 0){
				res.push_back(st.top()->val);
				flag[st.top()] = 1;
				temp = st.top()->right;
				st.pop();
			}
			else {
				temp = st.top()->right;
				st.pop();
			}
		}
	}
	return res;
}
ListNode* insertionSortList(ListNode* head) {
	if (!head)	return nullptr;
	ListNode* res = new ListNode(-1);		//头结点
	res->next = head;
	ListNode* tail = head;					//已排序部分尾结点
	ListNode* temp = tail->next;			//当前排序结点
	while (temp) {
		ListNode* temp0 = res->next, *behind = res;	//当前比较结点及其前一结点
		while (behind != tail) {
			if (temp0->val > temp->val) {	//找到应放置位置
				tail->next = temp->next;
				behind->next = temp;
				temp->next = temp0;
				break;
			}
			temp0 = temp0->next;
			behind = behind->next;
		}
		if (behind == tail)
			tail = tail->next;
		temp = tail->next;
	}
	return res->next;
}
ListNode* ListMerge(ListNode* head, ListNode* mid) {
	ListNode* H = new ListNode(-1);
	H->next = (head->val <= mid->val) ? head : mid;
	ListNode* p, *q;
	while (head && mid) {
		p = head->next;
		q = mid->next;
		if (head->val <= mid->val) {
			while (p && p->val <= mid->val) {
				head = p;
				p = p->next;
			}
			head->next = mid;
			head = p;
		}
		else {
			while (q && q->val <= head->val) {
				mid = q;
				q = q->next;
			}
			mid->next = head;
			mid = q;
		}
	}
	return H->next;
}
ListNode* sortList(ListNode* head) {
	if (!head || !head->next)
		return head;
	ListNode *H = new ListNode(-1);
	H->next = head;
	ListNode *fast, *mid;
	fast = mid = H;
	//快慢指针找出链表中点
	while (fast && fast->next) {
		mid = mid->next;
		fast = fast->next->next;
	}
	fast = mid->next;
	mid->next = nullptr;	//切断前后两段两链表
	mid = fast;

	head = sortList(head);
	mid = sortList(mid);
	return ListMerge(head, mid);
}
struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}
int maxPoints(vector<Point>& points) {
	if (points.empty())
		return 0;
	int len = points.size();
	int max(0);
	map<pair<int, int>, int> nums;
	int vertical = 1, same = 0;
	for (int i = 0; i != len; ++i) {
		for (int j = 0; j != len; ++j) {
			if (j == i)
				continue;
			if (points[i].x == points[j].x && points[i].y == points[j].y) {
				++same;
				continue;
			}
			int dx = points[i].x - points[j].x;
			int dy = points[i].y - points[j].y;
			int g = gcd(dx, dy);
			dx /= g, dy /= g;
			if (dx == 0)
				++vertical;
			else if (nums.find({ dx, dy }) == nums.end())
				nums[{ dx, dy }] = 2;
			else
				++nums[{ dx, dy }];
		}
		for (auto temp : nums) {
			if (temp.second + same > max)
				max = temp.second + same;
		}
		if (vertical + same > max)
			max = vertical + same;
		nums.clear();
		vertical = 1;
		same = 0;
	}
	return max;
}
int evalRPN(vector<string>& tokens) {
	if (tokens.empty())
		return 0;
	stack<int> st;
	int len = tokens.size();
	for (int i = 0; i != len; ++i) {
		if (tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "*" && 
			tokens[i] != "/"&&tokens[i] != "%") {
			int temp = 0, flag = 1;
			if (tokens[i][0] == '-')
				flag = -1;
			else 
				temp = tokens[i][0] - '0';
			for (int j = 1; j != tokens[i].size(); ++j) {
				temp = temp * 10 + tokens[i][j] - '0';
			}
			st.push(flag * temp);
		}
		else {
			int num1 = st.top();
			st.pop();
			int num2 = st.top();
			st.pop();
			if (tokens[i] == "+")
				st.push(num2 + num1);
			else if (tokens[i] == "-")
				st.push(num2 - num1);
			else if (tokens[i] == "*")
				st.push(num2 * num1);
			else if (tokens[i] == "/")
				st.push(num2 / num1);
			else if (tokens[i] == "%")
				st.push(num2 % num1);
		}
	}
	return st.top();
}
void reverseWords(string &s) {
	if (s.empty())	return;
	int left, right;
	for (int i = s.size() - 1; i != -1; --i) {
		if (s[i] == ' ')
			s.pop_back();
		else
			break;
	}
	int len = s.size();
	if (len == 0)	return;
	for (int i = s.size() - 1; i > -1; --i) {
		while (i > -1 && s[i] == ' ')
			--i;
		right = i;
		while (i > -1 && s[i] != ' ')
			--i;
		left = i;
		s += ' ';
		s += s.substr(left + 1, right - left);
	}
	s.erase(s.begin(), s.begin() + len + 1);
	s.pop_back();
}
int maxProduct(vector<int>& nums) {
	if (nums.empty())	return 0;
	int len = nums.size();
	int a = nums[0], b = nums[0], res = nums[0];
	for (int i = 1; i != len; ++i) {
		int tempa = a;
		a = max(nums[i], max(tempa * nums[i], b * nums[i]));
		b = min(nums[i], min(tempa * nums[i], b * nums[i]));
		res = max(a, res);
	}
	return res;
}
int findMin(vector<int>& nums) {
	int len = nums.size();
	int left = 0, right = len - 1, mid = (left + right) / 2;
	while (left <= right) {
		mid = left + (right - left) / 2;	//需要保证不能 int 相加出现溢出
		if (nums[mid] > nums[right]) {		//让中位数和右边的数字比较
			left = mid + 1;
		}
		else if (nums[mid] < nums[right]) {
			right = mid;					//因为这里的 right 可能就是最小值，不能加一
		}
		else {								//如果中间和最后相等。怎么查找，主要前后移动方向不确定
			right--;						//无法确定的时候，让 右边的值自减就好了
		}
	}
	return nums[left];
}
class MinStack {
public:
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		st.push(x);
		++minst[x];
	}

	void pop() {
		if (minst[st.top()] != 1)
			--minst[st.top()];
		else
			minst.erase(st.top());
		st.pop();
	}

	int top() {
		return st.top();
	}

	int getMin() {
		return minst.begin()->first;
	}
private:
	stack<int> st;
	map<int, int> minst;
};
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	if (!headA || !headB)
		return nullptr;
	unordered_set<ListNode*> flag;
	ListNode *a = headA, *b = headB;
	while (a) {
		flag.insert(a);
		a = a->next;
	}
	while (b) {
		if (flag.find(b) != flag.end())
			return b;
		else
			b = b->next;
	}
	return nullptr;
}
int findPeakElement(vector<int>& nums) {
	//规律一：如果nums[i] > nums[i+1]，则在i之前一定存在峰值元素
	//规律二：如果nums[i] < nums[i + 1]，则在i + 1之后一定存在峰值元素
	int left = 0, right = nums.size() - 1;
	while (left < right) {
		int mid = (left + right) / 2;
		if (nums[mid] > nums[mid + 1]) 
			right = mid;
		else 
			left = mid + 1;
	}
	return right;
}
int helpcmpvers(string str1, string str2) {
	int begin1 = 0, begin2 = 0;
	while (str1[begin1] == '0')
		++begin1;
	while (str2[begin2] == '0')
		++begin2;
	if (str1.substr(begin1, str1.size() - begin1).empty() && str2.substr(begin2, str2.size() - begin2).empty())
		return 0;
	else if (str1.substr(begin1, str1.size() - begin1).empty())
		return -1;
	else if (str2.substr(begin2, str2.size() - begin2).empty())
		return 1;
	int temp1 = stoi(str1.substr(begin1, str1.size() - begin1));
	int temp2 = stoi(str2.substr(begin2, str2.size() - begin2));
	if (temp1 > temp2)
		return 1;
	else if (temp1 < temp2)
		return -1;
	else
		return 0;
}
int compareVersion(string version1, string version2) {
	int len1 = version1.size(), len2 = version2.size();
	string temp1, temp2;
	int i, j;
	for (i = 0, j = 0; i < len1 && j < len2; ++i, ++j) {
		while (i < len1 && version1[i] != '.')
			temp1.push_back(version1[i++]);
		while (j < len2 && version2[j] != '.')
			temp2.push_back(version2[j++]);
		int tempres = helpcmpvers(temp1, temp2);
		if (tempres != 0)
			return tempres;
		temp1.clear();
		temp2.clear();
	}
	if (i - 1 == len1 && j - 1 == len2)
		return 0;
	else if (i < len1) {
		if (version1.substr(i, len1 - i).find_first_not_of("0.") != -1)
			return 1;
		else
			return 0;
	}
	else {
		if (version2.substr(j, len2 - j).find_first_not_of("0.") != -1)
			return -1;
		else
			return 0;
	}
}
string fractionToDecimal(int numerator, int denominator) {
	string res;
	map<int, int> flag;
	while (numerator >= denominator) {
		res.push_back(numerator / denominator + '0');
		numerator %= denominator;
		if (numerator == 0)
			return res;
	}
	if (res.empty())
		res.push_back('0');
	res.push_back('.');
	while (1) {
		numerator *= 10;
		if (flag.find(numerator % denominator) == flag.end())
			flag[numerator % denominator] = 0;
		else {
			numerator /= 10;
			break; 
		}
		res.push_back(numerator / denominator + '0');
		numerator %= denominator;
		if (numerator == 0)
			return res;
	}
	int circle_len = 0;
	string temp;
	while (1) {
		numerator *= 10;
		if (flag[numerator % denominator] != 1) {
			++circle_len;
			++flag[numerator % denominator];
			temp.push_back(numerator / denominator + '0');
			numerator %= denominator;
		}
		else
			break;
	}
	res.erase(res.size() - circle_len);
	res.push_back('(');
	res += temp;
	res.push_back(')');
	return res;
}
vector<int> twoSum(vector<int>& numbers, int target) {
	int len = numbers.size();
	int hot, left, right, mid;
	for (int i = 0; i != len; ++i) {
		hot = i;
		left = hot + 1, right = len - 1;
		while (left <= right) {
			mid = left + (right - left) / 2;
			if (numbers[hot] + numbers[mid] < target)
				left = mid + 1;
			else if (numbers[hot] + numbers[mid] > target)
				right = mid - 1;
			else
				return { hot + 1, mid + 1 };
		}
	}
}
string convertToTitle(int n) {
	if (n < 1)
		return "";
	string res;
	while (n != 0) {
		res.insert(res.begin(), (n - 1) % 26 + 'A');
		n = (n - 1) / 26;
	}
	return res;
}
int majorityElement0(vector<int>& nums) {
	int len = nums.size();
	unordered_map<int, int> flag;
	for (int temp : nums) {
		if (flag.find(temp) == flag.end()) {
			flag.insert({ temp, 1 });
		}
		else {
			++(*flag.find(temp)).second;
		}
		if ((*flag.find(temp)).second >= len / 2)
			return temp;
	}
}
int titleToNumber(string s) {
	if (s.empty())
		return 0;
	int res = 0;
	for (char temp : s) {
		res = res * 26 + (temp - 64);
		cout << temp << " " <<res << endl;
	}
	return res;
}
int trailingZeroes(int n) {
	int res = 0;
	int tail = n % 10;
	res += (tail >= 5) ? 1 : 0;
	res += 2 * n / 10;
	return res;
}
int calculateMinimumHP(vector<vector<int>>& dungeon) {
	//pair中第一项为初始为0情况下当前血量，第二项为过程中扣除的最大值。
	int row = dungeon.size(), col = dungeon[0].size();
	vector<vector<pair<int, int>>> flag(row, vector<pair<int, int>>(col, { 0,0 }));
	flag[0][0] = { dungeon[0][0], dungeon[0][0] };
	for (int i = 1; i != row; ++i) {
		flag[i][0].first = flag[i - 1][0].first + dungeon[i][0];
		if (flag[i][0].first < flag[i - 1][0].second)
			flag[i][0].second = flag[i][0].first;
		else
			flag[i][0].second = flag[i - 1][0].second;
	}
	for (int j = 1; j != col; ++j) {
		flag[0][j].first = flag[0][j - 1].first + dungeon[0][j];
		if(flag[0][j].first < flag[0][j - 1].second)
			flag[0][j].second = flag[0][j].first;
		else
			flag[0][j].second = flag[0][j - 1].second;
	}
	for (int i = 1; i != row; ++i) {
		bool down = false;		//标记在计算当前行时，路线是否已经下降到当前行，是则标记为true
		for (int j = 1; j != col; ++j) {
			pair<int, int> up = flag[i - 1][j], left = flag[i][j - 1];
			if (!down) {
				int a, b;	//分别存储选择从上方或左方格子时所累计扣除的血量
				a = min(up.first + dungeon[i][j], up.second);
				b = min(left.first + dungeon[i][j], left.second);
				flag[i][j].second = max(a, b);	//从两者中找出较小的那个作为当前格子的累计扣除血量（负数）
				if (a >= b)
					flag[i][j].first = up.first + dungeon[i][j];
				else {
					down = true;
					flag[i][j].first = left.first + dungeon[i][j];
				}
			}
			else {
				flag[i][j].first = left.first + dungeon[i][j];
				flag[i][j].second = min(left.first + dungeon[i][j], left.second);
			}
		}
	}
	if (flag[row - 1][col - 1].second >= 0)
		return 1;
	else
		return -(flag[row - 1][col - 1].second - 1);
}
static bool cmp(string s1, string s2) {
	int len1 = s1.size(), len2 = s2.size();
	int loc = 0;
	while (loc < min(len1, len2)) {
		if (s1[loc] > s2[loc])
			return true;
		else if (s1[loc] < s2[loc])
			return false;
		else
			++loc;
	}
	if (loc == len1) {
		while (loc != len2) {
			if (s2[loc] > s2[0])
				return false;
			else if (s2[loc] < s2[0])
				return true;
			++loc;
		}
		return true;
	}
	else {
		while (loc != len1) {
			if (s1[loc] > s1[0])
				return true;
			else if (s1[loc] < s1[0])
				return true;
			++loc;
		}
		return false;
	}
}
string largestNumber(vector<int>& nums) {
	if (accumulate(nums.begin(), nums.end(), 0) == 0)
		return "0";
	int len = nums.size();
	vector<string> num;
	for (int temp : nums) {
		num.push_back(to_string(temp));
	}
	sort(num.begin(), num.end(), cmp);
	string res;
	for (string temp : num)
		res += temp;
	return res;
}
vector<string> findRepeatedDnaSequences(string s) {
	unordered_map<string, int> flag;
	int len = s.size();
	vector<string> res;
	for (int i = 0; i != len - 10; ++i) {
		string temp = s.substr(i, 10);
		if (flag.find(temp) == flag.end())
			flag.insert({ temp, 1 });
		else
			++(*flag.find(temp)).second;
	}
	for (auto str : flag) {
		if (str.second > 1)
			res.push_back(str.first);
	}
	return res;
}
void rotate(vector<int>& nums, int k) {
	int len = nums.size();
	if (len == 0 || len == 1)	return;
	int time = k % len;
	if (time == 0)	return;
	for (int i = 0; i != (len - time) / 2; ++i) {
		int temp = nums[i];
		nums[i] = nums[len - time - 1 - i];
		nums[len - time - 1 - i] = temp;
	}
	for (int j = 0; j != time / 2; ++j) {
		int temp = nums[len - time + j];
		nums[len - time + j] = nums[len - 1 - j];
		nums[len - 1 - j] = temp;
	}
	for (int k = 0; k != len / 2; ++k) {
		int temp = nums[k];
		nums[k] = nums[len - 1 - k];
		nums[len - 1 - k] = temp;
	}
}
uint32_t reverseBits(uint32_t n) {
	uint32_t res = 0;
	uint32_t temp = 2147483648;
	for (int i = 0; i != 32; ++i) {
		if (n % 2 == 1)
			res |= temp;
		n >>= 1;
		temp >>= 1;
	}
	return res;
}
int hammingWeight(uint32_t n) {
	int res = 0;
	for (int i = 0; i != 32; ++i) {
		if (n % 2 == 1)
			res += 1;
		n >>= 1;
	}
	return res;
}
int rob0(vector<int>& nums) {
	if (nums.empty())
		return 0;
	int len = nums.size();
	if (len == 1)
		return nums[0];
	if (len == 2)
		return max(nums[0], nums[1]);
	int res;
	vector<int> maxmoney(len, 0);
	maxmoney[0] = nums[0], maxmoney[1] = nums[1];
	for (int i = 2; i != len; ++i) {
		int tempmax = 0;
		for (int j = 0; j != i - 1; ++j) {
			if (maxmoney[j] + nums[i] > tempmax)
				tempmax = maxmoney[j] + nums[i];
		}
		maxmoney[i] = tempmax;
	}
	return max(maxmoney[len - 1], maxmoney[len - 2]);
}
vector<int> rightSideView(TreeNode* root) {
	if (!root)	return {};
	vector<int> res;
	queue<TreeNode*> qe;
	int roofsize = 1;
	TreeNode* temp = root;
	qe.push(temp);
	while (temp) {
		if(qe.front()->left)
			qe.push(qe.front()->left);
		if(qe.front()->right)
			qe.push(qe.front()->right);
		if (--roofsize == 0) {
			res.push_back(qe.front()->val);
			roofsize = qe.size() - 1;
		}
		qe.pop();
		temp = (!qe.empty()) ? qe.front() : nullptr;
	}
	return res;
}
void BFS(vector<vector<char>>& grid, pair<int, int> loc) {
	queue<pair<int, int>> qe;
	qe.push(loc); 
	grid[loc.first][loc.second] = '2';
	while (!qe.empty()) {
		pair<int, int> temp = qe.front();
		if (temp.first != 0 && grid[temp.first - 1][temp.second] == '1') {
			qe.push({ temp.first - 1, temp.second });
			grid[temp.first - 1][temp.second] = '2';
		}
		if (temp.second != 0 && grid[temp.first][temp.second - 1] == '1') {
			qe.push({ temp.first, temp.second - 1 });
			grid[temp.first][temp.second - 1] = '2';
		}
		if (temp.first != grid.size() - 1 && grid[temp.first + 1][temp.second] == '1') {
			qe.push({ temp.first + 1, temp.second });
			grid[temp.first + 1][temp.second] = '2';
		}
		if (temp.second != grid[0].size() - 1 && grid[temp.first][temp.second + 1] == '1') {
			qe.push({ temp.first, temp.second + 1 });
			grid[temp.first][temp.second + 1] = '2';
		}
		qe.pop();
	}
}
int numIslands(vector<vector<char>>& grid) {
	if (grid.empty())	return 0;
	int row = grid.size(), col = grid[0].size();
	int res = 0;
	for (int i = 0; i != row; ++i) {
		for (int j = 0; j != col; ++j) {
			if (grid[i][j] == '1') {
				BFS(grid, { i,j });
				++res;
			}
		}
	}
	return res;
}
int rangeBitwiseAnd(int m, int n) {
	/*
	对于m和n，找到他们从最高位开始完全相同的位，
	就是我们需要的结果.这也不难理解，m和n假如在
	最高位到x位之间的二进制位完全相同，这就说明
	在递增的过程中+1的操作永远没有改变过这些位，
	而相反第x-1到最后一位都至少改变过一次，而改
	变一定是0->1或者1->0，就是说在着m-n+1个操作
	数中至少有一个的第i位（i>=0 && i<=x-1）为0．
	因此，第x-1位之下全都为0,m和n从最高位开始的
	连续相同部分就是我们要的结果
	*/
	int offset = 0;
	while (m && n) {
		if (m == n) return m << offset;
		m >>= 1;
		n >>= 1;
		++offset;
	}
return 0;
}
bool isHappy(int n) {
	unordered_set<int> num;
	int res = 0, temp = n;
	while (res != 1) {
		res = 0;
		while (temp != 0) {
			res += (temp % 10)*(temp % 10);
			temp /= 10;
		}
		if (res == 1)
			return true;
		if (num.find(res) == num.end()) {
			num.insert(res);
			temp = res;
		}
		else
			return false;
	}
}
ListNode* removeElements(ListNode* head, int val) {
	ListNode* res = new ListNode(-1);
	res->next = head;
	ListNode* front = res, *temp = head;
	while (temp) {
		if (temp->val == val)
			front->next = temp->next;
		else
			front = temp;
		temp = temp->next;
	}
	return res->next;
}
int countPrimes0(int n) {
	if (n <= 2)	return 0;
	unordered_set<int> nums;
	nums.insert(2);
	for (int i = 3; i != n; ++i) {
		int temp = i;
		while (temp != 1) {
			bool flag = true;
			for (int div : nums) {
				if (temp % div == 0) {
					temp /= div;
					flag = false;
					break;
				}
			}
			if (flag) {
				nums.insert(temp);
				break;
			}
		}
	}
	return nums.size();
}
int countPrimes(int n) {
	vector<int> nums(n, 1);
	int count(0);
	for (int i = 2; i < n; ++i) {
		if (nums[i]) {
			++count;
			for (int j = 2; i * j < n; ++j) {
				nums[i * j] = 0;
			}
		}
	}
	return count;
}
bool isIsomorphic(string s, string t) {
	if (s.empty())	return true;
	unordered_map<char, char> word1, word2;
	int len = s.size();
	for (int i = 0; i != len; ++i) {
		if (word1.find(s[i]) == word1.end())
			word1.insert({ s[i], t[i] });
		else if ((*word1.find(s[i])).second != t[i])
			return false;

		if (word2.find(t[i]) == word2.end())
			word2.insert({ t[i], s[i] });
		else if ((*word2.find(t[i])).second != s[i])
			return false;
	}
	return true;
}
ListNode* reverseList(ListNode* head) {
	if (!head)	return head;
	ListNode* p = nullptr, *q = head;
	while (q->next) {
		ListNode* r = q->next;
		q->next = p;
		p = q;
		q = r;
		r = r->next;
	}
	q->next = p;
	return q;
}
bool Dfs(vector<vector<int>>& Cou, int num, vector<bool> flag){
	if (flag[num])
		return false;
	flag[num] = true;
	int len = Cou[num].size();
	for (int i = 0; i != len; ++i) {
		if (!Dfs(Cou, Cou[num][i], flag))
			return false;
	}
	return true;
}
bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
	vector<vector<int>> Cou(numCourses, vector<int>{});
	for (pair<int, int> temp : prerequisites)
		Cou[temp.first].push_back(temp.second);
	vector<bool> flag(numCourses, false);
	for (int i = 0; i != numCourses; ++i) {
		if (!Dfs(Cou, i, flag))
			return false;
		flag[i] = true;
	}
	return true;
}
class TrieNode {
public:
	char val;
	vector<TrieNode*> nblist;
	bool isword = false;
};
class Trie {
private:
	TrieNode* head;
public:
	/** Initialize your data structure here. */
	Trie() {
		head = new TrieNode();
	}

	TrieNode* gethead() {
		return head;
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		auto temp = head;
		int len = word.size();
		int loc = 0;
		while (loc != len) {
			int listlen = temp->nblist.size();
			int j = 0;
			while (j != listlen) {
				if (temp->nblist[j]->val == word[loc]) {
					temp = temp->nblist[j];
					break;
				}
				++j;
			}
			if(j == listlen)
				break;
			++loc;
		}
		for (int i = loc; i != len; ++i) {
			TrieNode* newnode = new TrieNode;
			newnode->val = word[i];
			temp->nblist.push_back(newnode);
			temp = newnode;
		}
		temp->isword = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		auto temp = head;
		int len = word.size();
		int loc = 0;
		while (loc != len) {
			int listlen = temp->nblist.size();
			int j = 0;
			while (j != listlen) {
				if (temp->nblist[j]->val == word[loc]) {
					temp = temp->nblist[j];
					break;
				}
				++j;
			}
			if (j == listlen)
				return false;
			++loc;
		}
		if (temp->isword)
			return true;
		else
			return false;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		auto temp = head;
		int len = prefix.size();
		int loc = 0;
		while (loc != len) {
			int listlen = temp->nblist.size();
			int j = 0;
			while (j != listlen) {
				if (temp->nblist[j]->val == prefix[loc]) {
					temp = temp->nblist[j];
					break;
				}
				++j;
			}
			if (j == listlen)
				return false;
			++loc;
		}
		return true;
	}
};
int minSubArrayLen(int s, vector<int>& nums) {
	if (nums.empty())	return 0;
	int len = nums.size();
	int res = INT_MAX;
	int left = 0, right = 0, sum = 0;
	while (right != len) {
		if (sum < s) {
			sum += nums[right];
			++right;
		}
		else {
			res = min(right - left, res);
			if (res == 1)
				return res;
			sum -= nums[left];
			++left;
		}
	}
	int leftlen = INT_MAX, leftsum = 0;
	for (int i = len - 1; i != -1; --i) {
		leftsum += nums[i];
		if (leftsum >= s) {
			leftlen = len - i;
			break;
		}
	}
	if (res == INT_MAX && leftlen == INT_MAX)
		return 0;
	return min(res, leftlen);
}
class WordDictionary {
private:
	Trie dic;
public:
	Trie show() {
		return dic;
	}
	/** Initialize your data structure here. */
	WordDictionary() {

	}

	/** Adds a word into the data structure. */
	void addWord(string word) {
		dic.insert(word);
	}

	bool Find(string word, TrieNode* node, int num) {
		while (num != word.size() && !node->nblist.empty()) {
			if (word[num] != '.') {
				int loc;
				for (loc = 0; loc != node->nblist.size(); ++loc) {
					if (node->nblist[loc]->val == word[num])
						break;
				}
				if (loc == node->nblist.size())
					return false;
				else
					return Find(word, node->nblist[loc], num + 1);
			}
			else {
				int len = node->nblist.size();
				int i;
				for (i = 0; i != len; ++i) {
					if (Find(word, node->nblist[i], num + 1))
						return true;
				}
				if (i == len)
					return false;
			}
		}
		if (num == word.size() && node->isword)
			return true;
		return false;
	}

	/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
	bool search(string word) {
		auto temp = dic.gethead();
		return Find(word, temp, 0);
	}
};
int helpRob(vector<int> nums) {
	int len = nums.size();
	int res;
	vector<int> maxmoney(len, 0);
	maxmoney[0] = nums[0], maxmoney[1] = nums[1];
	for (int i = 2; i != len; ++i) {
		int tempmax = 0;
		for (int j = 0; j != i - 1; ++j) {
			if (maxmoney[j] + nums[i] > tempmax)
				tempmax = maxmoney[j] + nums[i];
		}
		maxmoney[i] = tempmax;
	}
	return max(maxmoney[len - 1], maxmoney[len - 2]);
}
int rob(vector<int>& nums) {
	if (nums.empty())	return 0;
	int len = nums.size();
	if (len == 1)
		return nums[0];
	if (len == 2)
		return max(nums[0], nums[1]);
	vector<int> nums1(nums.begin(), nums.end() - 1),
		nums2(nums.begin() + 1, nums.end());
	return max(helpRob(nums1), helpRob(nums2));
}
int findKthLargest(vector<int>& nums, int k) {
	make_heap(nums.begin(), nums.end());
	int result;
	for (int i = 0; i<k; i++) {
		result = nums.front();
		pop_heap(nums.begin(), nums.end());
		nums.pop_back();
	}
	return result;
}
void helpCombSum(vector<vector<int>>& res, vector<bool> flag, 
	vector<int> temp, int k, int n, int loc) {
	if (temp.size() == k) {
		if(accumulate(temp.begin(), temp.end(), 0) == n)
			res.push_back(temp);
		return;
	}
	for (int i = loc + 1; i != 10; ++i) {
		if (flag[i - 1]) {
			temp.push_back(i);
			flag[i - 1] = false;
			helpCombSum(res, flag, temp, k, n, i);
			temp.pop_back();
			flag[i - 1] = true;
		}
	}
}
vector<vector<int>> combinationSum3(int k, int n) {
	vector<bool> flag(9, true);
	vector<vector<int>> res;
	vector<int> temp;
	helpCombSum(res, flag, temp, k, n, 0);
	return res;
}
bool containsDuplicate(vector<int>& nums) {
	if (nums.empty())	return false;
	unordered_set<int> flag;
	for (int temp : nums) {
		if (flag.find(temp) == flag.end())
			flag.insert(temp);
		else
			return true;
	}
	return false;
}
bool containsNearbyDuplicate(vector<int>& nums, int k) {
	int len = nums.size();
	if (len < 1)
		return false;
	unordered_map<int, set<int>> flag;
	for (int i = 0; i != len; ++i)
		flag[nums[i]].insert(i);
	for (auto temp : flag) {
		auto left = temp.second.begin();
		while (1) {
			auto hot = left;
			if (++hot != temp.second.end()) {
				if (abs(*left - *hot) <= k)
					return true;
				left = hot;
			}
			else
				break;
		}
	}
	return false;
}
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
	if (nums.size() == 0) return false;
	multiset<long long> st;
	for (int i = 0; i < nums.size(); i++)
	{
		if (i > k) st.erase(st.find(static_cast<long long>(nums[i - k - 1])));
		auto it = st.lower_bound(static_cast<long long>(nums[i] - t));
		if (it != st.end() && llabs(*it - static_cast<long long>(nums[i]) <= t))
			return true;
		st.insert(static_cast<long long>(nums[i]));
	}
	return false;
}
int maximalSquare(vector<vector<char>>& matrix) {
	if (matrix.empty() || matrix[0].empty()) return 0;
	int m = matrix.size(), n = matrix[0].size(), res = 0;
	vector<vector<int>> dp(m, vector<int>(n, 0));
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == 0 || j == 0) dp[i][j] = matrix[i][j] - '0';
			else if (matrix[i][j] == '1') {
				dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
			}
			res = max(res, dp[i][j]);
		}
	}
	return res * res;
}
int height(TreeNode* root) {
	if (root == NULL)
		return -1;
	while (root != NULL)
		return height(root->left) + 1;
}
int countNodes(TreeNode* root) {
	int h = height(root);
	int nums = 0;
	while (root != NULL) {
		if (h - 1 == height(root->right)) { //左子树为满
			nums += 1 << h;		//相当于pow(2,h - 1)
			root = root->right;
		}
		else {		//右子树为满，且深度少1
			nums += 1 << h - 1;
			root = root->left;
		}
		h--;
	}
	return nums;
}
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
	/*
	int u1 = D, u2 = H;
	int d1 = B, d2 = F;
	int l1 = A, l2 = E;
	int r1 = C, r2 = G;
	*/
	int shade;
	int hight1 = min(D - F, H - B);
	int hight2 = min(D - B, H - F);
	int hight = min(hight1, hight2);

	int width1 = min(C - E, G - A);
	int width2 = min(C - A, G - E);
	int width = min(width1, width2);
	if (hight <= 0 || width <= 0)
		shade = 0;
	else
		shade = hight * width;
	return (C - A) * (D - B) + (G - E) * (H - F) - shade;
}
class MyStack {
	/*["MyStack","push","push","top","pop","empty"]
[[],[1],[2],[],[],[]]*/
private:
	queue<int> qst;
public:
	/** Initialize your data structure here. */
	MyStack() {

	}

	/** Push element x onto stack. */
	void push(int x) {
		qst.push(x);
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		int len = qst.size();
		for (int i = 1; i != len; ++i) {
			int temp = qst.front();
			qst.pop();
			qst.push(temp);
		}
		int temp = qst.front();
		qst.pop();
		return temp;
	}

	/** Get the top element. */
	int top() {
		int len = qst.size();
		for (int i = 1; i != len; ++i) {
			int temp = qst.front();
			qst.pop();
			qst.push(temp);
		}
		int temp = qst.front();
		qst.pop();
		qst.push(temp);
		return temp;
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return qst.empty();
	}
};
TreeNode* invertTree(TreeNode* root) {
	if (root) {
		TreeNode* temp = root->left;
		root->left = root->right;
		root->right = temp;
		invertTree(root->left);
		invertTree(root->right);
	}
	return root;
}
int calculate(string s) {
	int res = 0, num = 0, n = s.size();
	char op = '+';
	stack<int> st;
	for (int i = 0; i < n; ++i) {
		if (s[i] >= '0') {
			num = num * 10 + s[i] - '0';
		}
		if ((s[i] < '0' && s[i] != ' ') || i == n - 1) {
			if (op == '+') st.push(num);
			if (op == '-') st.push(-num);
			if (op == '*' || op == '/') {
				int tmp = (op == '*') ? st.top() * num : st.top() / num;
				st.pop();
				st.push(tmp);
			}
			op = s[i];
			num = 0;
		}
	}
	while (!st.empty()) {
		res += st.top();
		st.pop();
	}
	return res;
}
vector<string> summaryRanges(vector<int>& nums) {
	vector<string> ans;
	if (nums.empty()) return ans;
	int val = nums[0];
	for (int i = 1; i<nums.size(); ++i)
		if (nums[i] != nums[i - 1] + 1) {
			if (val == nums[i - 1]) ans.push_back(to_string(val));
			else ans.push_back(to_string(val) + "->" + to_string(nums[i - 1]));
			val = nums[i];
		}
	if (val == nums.back()) ans.push_back(to_string(val));
	else ans.push_back(to_string(val) + "->" + to_string(nums.back()));
	return ans;
}
vector<int> majorityElement(vector<int>& nums) {
	if (nums.empty())	return {};
	int len = nums.size();
	if (len == 1)
		return { nums[0] };
	else if (len == 2) {
		if (nums[0] == nums[1])
			return { nums[0] };
		else
			return { nums[0],nums[1] };
	}
	map<int, int> flag;
	flag[nums[0]] = 1;
	flag[nums[1]] = 1;
	for (int i = 2; i != len; ++i) {
		bool full = (flag.size() == 2 ? true : false);
		if (flag.find(nums[i]) == flag.end()) {
			for (auto temp = flag.begin(); temp != flag.end(); ++temp)
				--temp->second;
			for (auto temp : flag)
				if (temp.second == 0)
					flag.erase(temp.first);
			if (!full) {
				flag[nums[i]] = 1;
				full = true;
			}
		}
		else
			++(*flag.find(nums[i])).second;
	}
	vector<int> res;
	for (auto temp : flag)
		res.push_back(temp.first);
	return res;
}
int kthSmallest(TreeNode* root, int k) {
	stack<TreeNode*> st;
	TreeNode* temp = root;
	int num = 0;
	while (temp || !st.empty()) {
		while (temp) {
			st.push(temp);
			temp = temp->left;
		}
		temp = st.top();
		if (++num == k)
			return temp->val;
		st.pop();
		temp = temp->right;
	}
}
bool isPowerOfTwo(int n) {
	if (n <= 0)	return false;
	int bit = 0;
	for (int i = 0; i != 32; ++i, n = n >> 1)
		if (n & 1 == 1)	++bit;
	return (bit == 1 ? true : false);
}
class MyQueue {
private:
	stack<int> st1, st2;
public:
	/** Initialize your data structure here. */
	MyQueue() {

	}

	/** Push element x to the back of queue. */
	void push(int x) {
		st1.push(x);
	}

	/** Removes the element from in front of queue and returns that element. */
	int pop() {
		while (st1.size() != 1) {
			st2.push(st1.top());
			st1.pop();
		}
		int res = st1.top();
		st1.pop();
		while (!st2.empty()) {
			st1.push(st2.top());
			st2.pop();
		}
		return res;
	}

	/** Get the front element. */
	int peek() {
		while (st1.size() != 1) {
			st2.push(st1.top());
			st1.pop();
		}
		int res = st1.top();
		while (!st2.empty()) {
			st1.push(st2.top());
			st2.pop();
		}
		return res;
	}

	/** Returns whether the queue is empty. */
	bool empty() {
		return st1.empty();
	}
};
ListNode* helpPalindrome(ListNode* head) {
	if (!head)	return head;
	ListNode* p = nullptr, *q = head;
	while (q->next) {
		ListNode* r = q->next;
		q->next = p;
		p = q;
		q = r;
		r = r->next;
	}
	q->next = p;
	return q;
}
bool isPalindrome(ListNode* head) {
	if (!head || !head->next)	return true;
	ListNode *slow = head, *fast = head->next;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	ListNode *temp = slow;
	slow = slow->next;
	temp->next = nullptr;

	ListNode* right = helpPalindrome(slow), *left = head;
	while (right) {
		if (left->val != right->val)
			return false;
		right = right->next;
		left = left->next;
	}
	return true;
}
TreeNode* lowestCommonAncestor0(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (root == p || root == q)	return root;
	int pval = p->val, qval = q->val;
	unordered_set<TreeNode*> pAncestor;
	vector<TreeNode*> qAncestor;
	TreeNode* temp = root;
	while (1) {
		pAncestor.insert(temp);
		if (temp->val > pval)
			temp = temp->left;
		else if (temp->val < pval)
			temp = temp->right;
		else
			break;
	}
	temp = root;
	while (1) {
		qAncestor.push_back(temp);
		if (temp->val > qval)
			temp = temp->left;
		else if (temp->val < qval)
			temp = temp->right;
		else
			break;
	}
	for (int i = qAncestor.size() - 1; i != -1; --i) {
		if (pAncestor.find(qAncestor[i]) != pAncestor.end())
			return qAncestor[i];
	}
}
void GetNodePath(TreeNode *pRoot, int tar, vector<TreeNode*> &path) {
	path.push_back(pRoot);
	if (pRoot->val == tar)
		return;
	if (path.back()->val != tar && pRoot->left != nullptr)
		GetNodePath(pRoot->left, tar, path);
	if (path.back()->val != tar && pRoot->right != nullptr)
		GetNodePath(pRoot->right, tar, path);
	if (path.back()->val != tar)
		path.pop_back();
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (root == p || root == q)	return root;
	int pval = p->val, qval = q->val;
	vector<TreeNode*> pAncestor, qAncestor;
	GetNodePath(root, pval, pAncestor);
	GetNodePath(root, qval, qAncestor);
	int len = min(pAncestor.size(), qAncestor.size());
	TreeNode* res;
	for (int i = 0; i != len; ++i) {
		if (pAncestor[i] == qAncestor[i])
			res = pAncestor[i];
	}
	return res;
}
void deleteNode(ListNode* node) {
	ListNode* behind;
	while (node->next) {
		node->val = node->next->val;
		behind = node;
		node = node->next;
	}
	behind->next = nullptr;
}
vector<int> productExceptSelf(vector<int>& nums) {
	int len = nums.size();
	vector<int> left(len, nums[0]), right(len, nums[len - 1]), res(len, 0);
	for (int i = 1; i != len; ++i) {
		left[i] = left[i - 1] * nums[i];
		right[len - 1 - i] = right[len - i] * nums[len - 1 - i];
	}
	res[0] = right[1], res[len - 1] = left[len - 2];
	for (int i = 1; i != len - 1; ++i)
		res[i] = left[i - 1] * right[i + 1];
	return res;
}
bool searchMatrix(vector<vector<int>>& matrix, int target) {
	if (matrix.empty() || matrix[0].empty())	return false;
	int row = matrix.size(), col = matrix[0].size();
	if (target<matrix[0][0] || target > matrix[row - 1][col - 1])	return false;
	int minboard = min(row, col), maxboard = max(row, col);
	int loc = 0;
	while (loc != minboard) {
		if (target == matrix[loc][loc])	return true;
		else if (target < matrix[loc][loc])	break;
		++loc;
	}
	int colflag = col;
	for (int i = 0; i != loc; ++i) {
		for (int j = loc; j != colflag; ++j) {
			if (matrix[i][j] == target)	return true;
			else if (matrix[i][j] > target) {
				colflag = j;
				break;
			}
		}
	}
	int rowflag = row;
	for (int j = 0; j != loc; ++j){
		for (int i = loc; i != rowflag; ++i) {
			if (matrix[i][j] == target)	return true;
			else if (matrix[i][j] > target) {
				rowflag = i;
				break;
			}
		}
	}
	return false;
}
void helpCompute(vector<int> &res, vector<int> nums, vector<char> opt, int loc) {
	int temp;
	if (opt[loc] == '+')
		temp = nums[loc] + nums[loc + 1];
	else if (opt[loc] == '-')
		temp = nums[loc] - nums[loc + 1];
	else if (opt[loc] == '*')
		temp = nums[loc] * nums[loc + 1];
	nums.erase(nums.begin() + loc, nums.begin() + loc + 2);
	nums.insert(nums.begin() + loc, temp);
	opt.erase(opt.begin() + loc);
	if (nums.size() == 1)
		res.push_back(temp);
	else
		for (int i = 0; i != nums.size() - 1; ++i)
			helpCompute(res, nums, opt, i);
}
void divNumOpt(const string input, int len, vector<int>& nums, vector<char>& opt) {
	for (int i = 0; i != len; ++i) {
		if (input[i] == '+' || input[i] == '-' || input[i] == '*')
			opt.push_back(input[i]);
		else {
			int temp = 0;
			while (i != len && input[i] >= '0' && input[i] <= '9') {
				temp = temp * 10 + (input[i++] - '0');
			}
			nums.push_back(temp);
			--i;
		}
	}
}
vector<int> diffWaysToCompute(string input) {
	int len = input.size();
	if (len == 1)	return { input[0] };
	vector<int> nums, res;
	vector<char> opt;
	divNumOpt(input, len, nums, opt);
	if (nums.size() == 1)
		return { nums[0] };
	for (int loc = 0; loc != nums.size() - 1; ++loc)
		helpCompute(res, nums, opt, loc);
	return res;
}
bool isAnagram(string s, string t) {
	if (s.size() != t.size())	return false;
	int len = s.size();
	unordered_map<char, int> flag;
	for (int i = 0; i != len; ++i) {
		if (flag.find(s[i]) == flag.end())
			flag.insert({ s[i],1 });
		else
			++(*flag.find(s[i])).second;
	}
	for (int j = 0; j != len; ++j) {
		if (flag.find(t[j]) == flag.end())
			flag.insert({ t[j],1 });
		else
			if ((--(*flag.find(t[j])).second) == 0)
				flag.erase(t[j]);
	}
	return flag.empty();
}
void helpPaths(TreeNode* root, string temp, vector<string>& res) {
	int tval = root->val;
	temp = temp + "->" + to_string(tval);
	if(root->left)
		helpPaths(root->left, temp, res);
	if(root->right)
		helpPaths(root->right, temp, res);
	if (!root->left && !root->right)
		res.push_back(temp);
}
vector<string> binaryTreePaths(TreeNode* root) {
	if (!root)	return {};
	vector<string> res;
	string temp = (to_string(root->val));
	if (!root->left && !root->right)	return { temp };
	if (root->left)
		helpPaths(root->left, temp, res);
	if (root->right)
		helpPaths(root->right, temp, res);
	return res;
}
int addDigits(int num) {
	if (num < 10)	return num;
	int res = num;
	vector<int> bit;
	do {
		while (res != 0) {
			bit.push_back(res % 10);
			res /= 10;
		}
		res = 0;
		for (int b : bit)
			res += b;
		bit.clear();
	} while (res >= 10);
	return res;
}
bool isUgly(int num) {
	if (num <= 0)
		return false;
	while (num != 1) {
		if (num % 2 == 0)
			num /= 2;
		else if (num % 3 == 0)
			num /= 3;
		else if (num % 5 == 0)
			num /= 5;
		else
			return false;
	}
	return true;
}
int nthUglyNumber0(int n) {
	if (n == 1)	return 1;
	vector<int> UgNum{ 1,2,3 };
	for (int i = 3; i < n; ++i) {
		long min2, min3, min5, x, y, z;
		for (x = i - 1; x >= 0 && 2 * static_cast<long>(UgNum[x]) > UgNum[i - 1]; --x)
			min2 = 2 * static_cast<long>(UgNum[x]);
		for (y = x; y >= 0 && 3 * static_cast<long>(UgNum[y]) > UgNum[i - 1]; --y)
			min3 = 3 * static_cast<long>(UgNum[y]);
		for (z = y; z >= 0 && 5 * static_cast<long>(UgNum[z]) > UgNum[i - 1]; --z)
			min5 = 5 * static_cast<long>(UgNum[z]);
		UgNum.push_back(min(min(min2, min3), min5));
	}
	return UgNum.back();
}
int nthUglyNumber(int n) {
	int start = 1;

	vector<int> res;      //存放结果
	res.push_back(start);   //第一个数先放进去
	if (n == 1)    //处理特殊情况
		return 1;
	int index = 1;   //序列号
	int p2, p3, p5;   //记录的是当前乘以2，3，5的数的索引。
	p2 = p3 = p5 = 0;   //所以初始化为1，每次枚举三个数
	while (index<n)
	{
		res.push_back(min(2 * res[p2], min(3 * res[p3], 5 * res[p5])));   //每次把最小的放入数组
		if (2 * res[p2] == *(res.end() - 1))   p2++;
		//如果刚放入的是2*res[p2],就把p2++,下次就用下一个数乘以2了。
		if (3 * res[p3] == *(res.end() - 1))   p3++;
		if (5 * res[p5] == *(res.end() - 1))   p5++;
		//上面三个if之间不要用else，因为可能存在多个最小值，都需加1。
		index++;            //索引加1，
	}
	return *(res.end() - 1);   //返回最后一个数
							   // write your code here
}
int missingNumber(vector<int>& nums) {
	if (nums.empty())	return 0;
	int res = nums[0] ^ 0, len = nums.size(), loc = 1;
	while (loc != len) {
		res = res ^ nums[loc] ^ loc;
		++loc;
	}
	return res ^ loc;
}
string numberToWords(int num) {
	int digit = 0, tmp = num;
	while (tmp != 0) {
		++digit;
		tmp /= 10;
	}
	vector<string> group(digit / 3);
	return {};
}
int hIndex0(vector<int>& citations) {
	sort(citations.rbegin(), citations.rend());
	for (int i = 0; i < citations.size(); ++i) {
		if (i >= citations[i]) return i;
	}
	return citations.size();
}
int hIndex(vector<int>& citations) {
	int len = citations.size();
	int left = 0, right = len - 1, mid;
	while (left <= right) {
		mid = left + (right - left) / 2;
		if (len - mid > citations[mid])
			left = mid + 1;
		else if (len - mid <= citations[mid])
			right = mid - 1;
	}
	return len - mid;
}
int helpSquares(int loc, int tmptm, vector<int> res, set<int>& times) {
	int roof = static_cast<int>(sqrt(loc));
	for (int i = 1; i != roof + 1; ++i) {
		times.insert(tmptm + res[i * i - 1] + res[loc - i * i]);
		vector<int> temp(res.begin(), res.end() - i * i);
		helpSquares(loc - i * i, res[i * i - 1], temp, times);
	}
	return *times.begin();
}
int numSquares(int n) {
	vector<int> res(n, 0);
	set<int> times;
	res[0] = 1;
	for (int i = 1; i * i - 1 < n; ++i)
		res[i * i - 1] = 1;
	for (int i = 1; i != n; ++i) {
		if (res[i] != 0)	continue;
		vector<int> temp(res.begin(), res.begin() + i + 1);
		res[i] = helpSquares(i, 0, temp, times);
		times.clear();
	}
	return res.back();
}
void moveZeroes(vector<int>& nums) {
	int len = nums.size();
	int ztime = 0;
	for (int i = 0; i < len; ++i) {
		if (nums[i] == 0) {
			++ztime;
			continue;
		}
		if (ztime) {
			nums[i - ztime] = nums[i];
			nums[i] = 0;
		}
	}
}
int findDuplicate(vector<int>& nums) {
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left < right) {
		int mid = left + (right - left) / 2;
		int count = 0;
		for (int i = 0; i != len; ++i)
			if (nums[i] <= mid)	++count;
		if (count > mid)
			right = mid;
		else
			left = mid + 1;
	}
	return left;
}
void gameOfLife(vector<vector<int>>& board) {
	int row = board.size(), col = board[0].size();
	for (int i = 0; i != row; ++i) {
		for (int j = 0; j != col; ++j) {
			int count = 0;
			if (i != 0 && (board[i - 1][j] == 1 || board[i - 1][j] == -2))
				++count;
			if (j != 0 && (board[i][j - 1] == 1 || board[i][j - 1] == -2))
				++count;
			if (i != row - 1 && (board[i + 1][j] == 1 || board[i + 1][j] == -2))
				++count;
			if (j != col - 1 && (board[i][j + 1] == 1 || board[i][j + 1] == -2))
				++count;
			if (i != 0 && j != 0 && (board[i - 1][j - 1] == 1 || board[i - 1][j - 1] == -2))
				++count;
			if (i != 0 && j != col - 1 && (board[i - 1][j + 1] == 1 || board[i - 1][j + 1] == -2))
				++count;
			if (i != row - 1 && j != 0 && (board[i + 1][j - 1] == 1 || board[i + 1][j - 1] == -2))
				++count;
			if (i != row - 1 && j != col - 1 && (board[i + 1][j + 1] == 1 || board[i + 1][j + 1] == -2))
				++count;
			
			if (board[i][j] == 1 && (count < 2 || count > 3))
				board[i][j] = -2;
			else if(board[i][j] == 0 && count == 3)
				board[i][j] = -1;
		}
	}
	for (int i = 0; i != row; ++i) {
		for (int j = 0; j != col; ++j) {
			if (board[i][j] == -2)
				board[i][j] = 0;
			else if (board[i][j] == -1)
				board[i][j] = 1;
		}
	}
}
bool wordPattern(string pattern, string str) {
	vector<string> part;
	for (int i = 0; i < str.size(); ++i) {
		string temp;
		while (i != str.size() && str[i] != ' ')
			temp.push_back(str[i++]);
		part.push_back(temp);
	}
	if (pattern.size() != part.size())	return false;
	unordered_map<char, string> flag1;
	unordered_map<string, char> flag2;
	for (int i = 0; i != pattern.size(); ++i) {
		if (flag1.find(pattern[i]) == flag1.end())
			flag1.insert({ pattern[i], part[i] });
		else if ((*flag1.find(pattern[i])).second != part[i])
			return false;
	}
	for (int i = 0; i != part.size(); ++i) {
		if (flag2.find(part[i]) == flag2.end())
			flag2.insert({ part[i], pattern[i] });
		else if ((*flag2.find(part[i])).second != pattern[i])
			return false;
	}
	return true;
}
class MedianFinder {
private:
	vector<int> lfnums, rtnums;
public:
	/** initialize your data structure here. */
	MedianFinder() {
		make_heap(lfnums.begin(), lfnums.end());
		make_heap(rtnums.begin(), rtnums.end(), greater<int>());
	}

	void addNum(int num) {
		if (lfnums.empty())	
			lfnums.push_back(num);
		else if (rtnums.empty()) {
			if (num >= lfnums[0])
				rtnums.push_back(num);
			else {
				rtnums.push_back(lfnums[0]);
				lfnums[0] = num;
			}
		}
		else if (lfnums.size() == rtnums.size()) {
			if (num <= rtnums[0]) {
				lfnums.push_back(num);
				push_heap(lfnums.begin(), lfnums.end());
			}
			else {
				lfnums.push_back(lfnums[0]);
				lfnums[0] = rtnums[0];
				rtnums[0] = num;
				make_heap(rtnums.begin(), rtnums.end(), greater<int>());
			}
		}
		else {
			if(num >= lfnums[0]) {
				rtnums.push_back(num);
				push_heap(rtnums.begin(), rtnums.end(), greater<int>());
			}
			else {
				rtnums.push_back(rtnums[0]);
				rtnums[0] = lfnums[0];
				lfnums[0] = num;
				make_heap(lfnums.begin(), lfnums.end());
			}
		}
	}

	double findMedian() {
		return lfnums.size() == rtnums.size() ? static_cast<double>(lfnums.front() + rtnums.front()) / 2.0 : static_cast<double>(lfnums.front());
	}
};
string getHint(string secret, string guess) {
	int len = secret.size(), bull = 0;
	unordered_map<char, int> flag;
	for (int i = 0; i != len; ++i) {
		if (secret[i] == guess[i])	++bull;
		if (flag.find(secret[i]) == flag.end())
			flag.insert({ secret[i],1 });
		else
			++(*flag.find(secret[i])).second;
	}
	int cows = 0 - bull;
	for (int i = 0; i != len; ++i) {
		if (flag.find(guess[i]) != flag.end()){
			++cows;
			if ((*flag.find(guess[i])).second == 1)
				flag.erase(guess[i]);
			else
				--(*flag.find(guess[i])).second;
		}
	}
	string res{ "0A0B" };
	res[0] = static_cast<char>(bull + '0');
	res[2] = static_cast<char>(cows + '0');
	return res;
}
int lengthOfLIS(vector<int>& nums) {
	if (nums.empty())	return 0;
	int len = nums.size();
	vector<int> flag(len, 1);
	int max = 0;
	for (int i = 0; i != len; ++i) {
		int before = 0;
		for (int j = 0; j != i; ++j) {
			if (nums[i] > nums[j] && flag[j] > before)
				before = flag[j];
		}
		flag[i] += before;
		if (flag[i] > max)
			max = flag[i];
	}
	return max;
}
/*
class NumArray {
private:
	vector<int> numbers;
	vector<vector<pair<bool, int>>> histroy;
public:
	NumArray(vector<int> nums) {
		numbers = nums;
		int len = nums.size();
		histroy = vector<vector<pair<bool, int>>>(len, vector<pair<bool, int>>(len, { false, 0 }));
	}

	int sumRange(int i, int j) {
		int sum = 0;
		vector<pair<int, int>> piece{ {i - 1,i - 1} };
		for (int row = i; row != j; ++row) {
			for (int col = row; col != j; ++col) {
				if (histroy[row][col].first) {
					sum += histroy[row][col].second;
					piece.push_back({ row, col });
					row = col;
					break;
				}
			}
		}
		piece.push_back({ j + 1,j + 1 });
		for (int times = 0; times != piece.size() - 1; ++times) {
			for (int loc = piece[times].second + 1; loc != piece[times + 1].first; ++loc) 
				sum += numbers[loc];
		}
		return sum;
	}
};
*/
class NumArray0 {
public:
	NumArray0(vector<int> nums) {
		dp.resize(nums.size() + 1, 0);
		for (int i = 1; i <= nums.size(); ++i) {
			dp[i] = dp[i - 1] + nums[i - 1];
		}
	}
	int sumRange(int i, int j) {
		return dp[j + 1] - dp[i];
	}

private:
	vector<int> dp;
};
class NumMatrix {
private:
	vector<vector<int>> numbers;
public:
	NumMatrix(vector<vector<int>> matrix) {
		int row = matrix.size(), col = matrix[0].size();
		numbers = vector<vector<int>>(row + 1, vector<int>(col + 1, 0));
		for (int i = 0; i != row; ++i) {
			for (int j = 0; j != col; ++j)
				numbers[i + 1][j + 1] = numbers[i + 1][j] + numbers[i][j + 1] - numbers[i][j] + matrix[i][j];
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return numbers[row2 + 1][col2 + 1] - numbers[row2 + 1][col1] - numbers[row1][col2 + 1] + numbers[row1][col1];
	}
};
class NumArray {
private:
	vector<pair<int, int>> hisSum;
public:
	NumArray(vector<int> nums) {
		hisSum.resize(nums.size() + 1, { 0, 0 });
		for (int i = 1; i <= nums.size(); ++i) {
			hisSum[i].first = nums[i - 1];
			hisSum[i].second = hisSum[i - 1].second + nums[i - 1];
		}
	}

	void update(int i, int val) {
		int def = val - hisSum[i + 1].first;
		hisSum[i + 1].first = val;
		while (i != hisSum.size() - 1) {
			hisSum[i + 1].second += def;
			++i;
		}
	}

	int sumRange(int i, int j) {
		return hisSum[j + 1].second - hisSum[i].second;
	}
};
vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
	unordered_map<int, unordered_set<int>> nodes;
	for (int i = 0; i != edges.size(); ++i) {
		if (nodes.find(edges[i].first) == nodes.end())
			nodes.insert({ edges[i].first, { edges[i].second } });
		else {
			if ((*nodes.find(edges[i].first)).second.find(edges[i].second) == (*nodes.find(edges[i].first)).second.end())
				(*nodes.find(edges[i].first)).second.insert(edges[i].second);
		}
		if (nodes.find(edges[i].second) == nodes.end())
			nodes.insert({ edges[i].second, { edges[i].first } });
		else {
			if ((*nodes.find(edges[i].second)).second.find(edges[i].first) == (*nodes.find(edges[i].second)).second.end())
				(*nodes.find(edges[i].second)).second.insert(edges[i].first);
		}
	}
	int res = INT_MAX;
	vector<int> RES;
	for (auto i = nodes.begin(); i != nodes.end(); ++i) {
		unordered_map<int, bool> flag;
		for (unordered_map<int, unordered_set<int>>::iterator j = nodes.begin(); j != nodes.end(); ++j)
			flag.insert({ j->first, true });
		queue<int> qe;
		int temp = i->first, res0 = 0, n = 0;
		flag.find(temp)->second = false;
		while (!qe.empty() || n != -1) {
			for (int nums : nodes.find(temp)->second) {
				if (flag.find(nums)->second) {
					qe.push(nums);
					flag.find(nums)->second = false;
				}
			}
			if (n == 0) {
				++res0;
				n = qe.size();
			}
			if (!qe.empty()) {
				temp = qe.front();
				qe.pop();
			}
			--n;
		}
		if (res0 < res) {
			res = res0;
			RES.clear();
			RES.push_back(i->first);
		}
		else if (res0 == res)
			RES.push_back(i->first);
	}
	return RES;
}
int nthSuperUglyNumber(int n, vector<int>& primes) {
	vector<int> res{ 1 };
	if (n == 1)	return 1;
	int loc = 1, len = primes.size();
	vector<int> index(len, 0);
	while (loc != n) {
		int min = INT_MAX;
		vector<int> flag;
		for (int i = 0; i != len; ++i) {
			if (primes[i] * res[index[i]] < min) {
				flag.clear();
				flag.push_back(i);
				min = primes[i] * res[index[i]];
			}
			else if (primes[i] * res[index[i]] == min)
				flag.push_back(i);
		}
		res.push_back(min);
		for (int j = 0; j != flag.size(); ++j)
			++index[flag[j]];
		++loc;
	}
	return res.back();
}
vector<int> countSmaller(vector<int>& nums) {
	if (nums.empty())	return {};
	int len = nums.size();
	vector<int> temp{ nums.back() }, res{ 0 };
	for (int i = len - 2; i != -1; --i) {
		auto pos = lower_bound(temp.begin(), temp.end(), nums[i]);
		res.push_back(pos - temp.begin());
		temp.insert(pos, nums[i]);
	}
	return vector<int>(res.rbegin(), res.rend());
}
int maxProduct(vector<string>& words) {
	int n = words.size(), a, b, max = 0, t;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			a = 0;
			b = 0;
			for (char c : words[i]) {
				a |= 1 << (c - 'a');
			}
			for (char c : words[j]) {
				b |= 1 << (c - 'a');
			}
			t = words[i].length() * words[j].length();
			if (!(a & b) && t > max) {
				max = t;
			}
		}
	}
	return max;
}
int helpSwitch(int temp) {
	int roof = temp / 2;
	int res = 1;
	for (int i = 1; i != roof + 1; ++i)
		if (temp % i == 0)
			res = res ^ 1;
	return res;
}
int bulbSwitch(int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	int res = 1;
	for (int i = 2; i != n + 1; ++i)
		if (helpSwitch(i))
			++res;
	return res;
}
bool helpChange(vector<int>& coins, int amount, int loc, int& tmp, int& num) {
	if (tmp == amount)	return true;
	else if(tmp > amount)
		return false;
	bool a;
	for (int i = loc; i != -1; --i) {
		tmp += coins[i];
		a = helpChange(coins, amount, i, tmp, ++num);
		if (!a) {
			--num;
			tmp -= coins[i];
		}
		if (tmp == amount)	break;
	}
	return a ? true : false;
}
int coinChange(vector<int>& coins, int amount) {
	if (amount == 0)	return 0;
	if (coins.empty())	return -1;
	sort(coins.begin(), coins.end());
	if (amount < coins[0])	return -1;
	int tmp = 0, len = coins.size(), num = 0;
	for (int i = len - 1; i != -1; --i) {
		if (helpChange(coins, amount, i, tmp, num) != -1)
			return num == 0 ? -1 : num;
	}
}
void wiggleSort(vector<int> &nums) {
	sort(nums.begin(), nums.end());
	vector<int> temp = nums;
	int len = nums.size();
	int mid = (len + 1) / 2;
	for (int i = 0; i != mid; ++i) {
		nums[2 * i] = temp[mid - i - 1];
		if (2 * i + 1 != len)
			nums[2 * i + 1] = temp[len - i - 1];
	}
}
bool isPowerOfThree(int n) {
	if (n <= 0)	return false;
	int temp = 1;
	while (1) {
		if (temp == n)	return true;
		else if (temp >= INT_MAX / 3)	return false;
		else if (temp < n)
			temp *= 3;
		else
			return false;
	}
}
int countRangeSum(vector<int>& nums, int lower, int upper) {
	if (nums.empty())	return 0;
	int len = nums.size();
	vector<long long> nums0(nums.begin(), nums.end());
	vector<vector<long long>> sums(len, vector<long long>(len, 0));
	sums[0][0] = nums0[0];
	int res = (sums[0][0] >= lower && sums[0][0] <= upper ? 1 : 0);
	for (int i = 1; i != len; ++i) {
		sums[0][i] = sums[0][i - 1] + nums0[i];
		if (sums[0][i] >= lower && sums[0][i] <= upper)	++res;
		sums[i][i] = nums0[i];
		if (sums[i][i] >= lower && sums[i][i] <= upper)	++res;
	}
	for (int i = 1; i != len; ++i) {
		for (int j = i + 1; j != len; ++j) {
			sums[i][j] = sums[i][j - 1] + nums0[j];
			if (sums[i][j] >= lower && sums[i][j] <= upper)	++res;
		}
	}
	return res;
}
ListNode* oddEvenList(ListNode* head) {
	if (!head || !head->next)	return head;
	ListNode *p1 = head, *p2 = head->next, *head2 = head->next;
	bool flag = 1;
	while (1) {
		if (flag) {
			if (p2 && p2->next) {
				p1->next = p2->next;
				p1 = p1->next;
			}
			else
				break;
		}
		else {
			if (p1) {
				p2->next = p1->next;
				p2 = p2->next;
			}
			else
				break;
		}
		flag = flag ^ true;
	}
	p1->next = head2;
	return head;
}
bool isValidSerialization(string preorder) {
	if (preorder.empty())	return false;
	if (preorder == "#")	return true;
	stack<string> st;
	int len = preorder.size();
	string temp;
	for (int i = 0; i != len; ++i) {
		if (st.size() == 1 && st.top() == "#")
			return false;
		if (preorder[i] == ',') {
			if (!temp.empty()) {
				st.push(temp);
				temp.clear();
			}
		}
		else if (preorder[i] == '#') {
			string head;
			if (!st.empty()) {
				head = st.top();
				while (head == "#") {
					if (!st.empty()) st.pop();
					else return false;
					if (!st.empty()) st.pop();
					else return false;
					if (!st.empty()) head = st.top();
					else break;
				}
				st.push("#");
			}
		}
		else
			temp.push_back(preorder[i]);
	}
	return (st.size() == 1 && st.top() == "#") ? true : false;
}
bool increasingTriplet(vector<int>& nums) {
	int len = nums.size();
	if (len < 3)	return false;
	int minNum = INT_MAX;
	int middleNum = INT_MAX;
	for (int i = 0; i != len; ++i) {
		if (nums[i] <= minNum) {
			minNum = nums[i];
		}
		else if (nums[i] <= middleNum) {
			middleNum = nums[i];
		}
		else return true;
	}
	return false;
}
vector<int> countBits(int num) {
	if (num == 0)	return { 0 };
	vector<int> flag(num + 1, 0);
	int hot = 1;
	while (hot <= num) {
		flag[hot] = 1;
		hot *= 2;
	}
	int behind = 0;
	for (int i = 1; i != num + 1; ++i) {
		if (flag[i] == 1) {
			behind = i;
			continue;
		}
		else {
			flag[i] = flag[behind] + flag[i - behind];
		}
	}
	return flag;
}
int integerBreak(int n) {
	if (n < 5)	return n;
	vector<int> flag{ 1,2,3,4 };
	for (int loc = 4; loc != n; ++loc) {
		int temp = 0;
		for (int i = 0; i != loc / 2 + 1; ++i) {
			if (flag[i] * flag[loc - 1 - i] > temp)
				temp = flag[i] * flag[loc - 1 - i];
		}
		flag.push_back(temp);
	}
	return flag.back();
}
string reverseString(string s) {
	int len = s.size();
	string res;
	for (int i = 0; i != len; ++i)
		res.push_back(s[len - 1 - i]);
	return res;
}
bool isVowels(char word) {
	return (word == 'a' || word == 'e' || word == 'i' || word == 'o' || word == 'u' ||
		word == 'A' || word == 'E' || word == 'I' || word == 'O' || word == 'U');
}
string reverseVowels(string s) {
	int len = s.size();
	int left = 0, right = len - 1;
	while (left < right) {
		while (left != len && !isVowels(s[left]))
			++left;
		while (right != -1 && !isVowels(s[right]))
			--right;
		if (left < right) {
			char temp = s[left];
			s[left] = s[right];
			s[right] = temp;
			++left;
			--right;
		}
		else break;
	}
	return s;
}
vector<int> topKFrequent(vector<int>& nums, int k) {
	unordered_map<int, int> flag;
	for (int temp : nums) {
		if (flag.find(temp) == flag.end())
			flag.insert({ temp,1 });
		else
			++flag.find(temp)->second;
	}
	vector<int> hot(k, 0);
	for (pair<const int, int> temp : flag) {
		if (temp.second > hot.front()) {
			hot[0] = temp.second;
			make_heap(hot.begin(), hot.end(), greater<int>());
		}
	}
	vector<int> res;
	for (pair<const int, int> temp : flag) {
		if (temp.second >= hot.front())
			res.push_back(temp.first);
	}
	return res;
}
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
	vector<int> res;
	unordered_map<int, bool> flag;
	for (int num : nums1)
		flag.insert({ num,false });
	for (int num : nums2)
		if (flag.find(num) != flag.end())
			flag.find(num)->second = true;
	for (pair<const int, bool> temp : flag)
		if (temp.second)
			res.push_back(temp.first);
	return res;
}
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
	vector<int> res;
	unordered_map<int, int> flag;
	for (int num : nums1) {
		if (flag.find(num) == flag.end())
			flag.insert({ num,1 });
		else
			++flag.find(num)->second;
	}
	for (int num : nums2) {
		if (flag.find(num) != flag.end()) {
			res.push_back(num);
			if (--flag.find(num)->second == 0)
				flag.erase(num);
		}
	}
	return res;
}
int maxEnvelopes(vector<pair<int, int>>& envelopes) {
	if (envelopes.empty())	return 0;
	sort(envelopes.begin(), envelopes.end());
	vector<pair<pair<int, int>, int>> flag;
	int len = envelopes.size();
	for (int i = 0; i != len; ++i)
		flag.push_back({ envelopes[i], 1 });
	int res = 1;
	for (int i = 1; i != len; ++i) {
		int M = 0;
		for (int j = 0; j != i; ++j) {
			if (flag[i].first.first > flag[j].first.first && flag[i].first.second > flag[j].first.second && flag[j].second > M)
				M = flag[j].second;
		}
		flag[i].second += M;
		if (flag[i].second > res)
			res = flag[i].second;
	}
	return res;
}
int countNumbersWithUniqueDigits(int n) {
	if (n == 0)	return 1;
	vector<int > res{ 1 };
	for (int i = 1; i != n + 1; ++i) {
		int temp = 9;
		for (int j = 0; j != i - 1; ++j)
			temp *= (9 - j);
		res.push_back(temp + res[i - 1]);
	}
	return res.back();
}
bool isPerfectSquare(int num) {
	if (num <= 0)	return false;
	long long left = 0, right = num;
	while (left <= right) {
		long long mid = left + (right - left) / 2;
		if (mid * mid == static_cast<long long>(num))	return true;
		else if (mid * mid > static_cast<long long>(num))
			right = mid - 1;
		else
			left = mid + 1;
	}
	return false;
}
vector<int> largestDivisibleSubset(vector<int>& nums) {
	if (nums.empty())	return {};
	int len = nums.size();
	sort(nums.begin(), nums.end());
	// [值, {前一值的位置, 到此值时最长长度}]
	vector<pair<int, pair<int, int>>> flag;
	flag.push_back({ 1, {-1,1} });
	for (int i = 0; i != len; ++i)
		flag.push_back({ nums[i],{0,1} });
	int maxlen = 1, maxloc = 1;
	for (int i = 1; i != len + 1; ++i) {
		for (int j = i - 1; j != 0; --j) {
			if (flag[i].first % flag[j].first == 0 && flag[j].second.second + 1 > flag[i].second.second) {
				flag[i].second.first = j;
				flag[i].second.second = flag[j].second.second + 1;
				if (flag[i].second.second > maxlen) {
					maxlen = flag[i].second.second;
					maxloc = i;
				}
			}
		}
	}
	vector<int> res;
	do{
		res.push_back(flag[maxloc].first);
		maxloc = flag[maxloc].second.first;
	} while (flag[maxloc].second.first != -1);
	return res;
}
int getSum(int a, int b) {
	bool flag = false;
	int bit = 1, hide = 1, sum = 0;
	while (hide != 0) {
		int temp1 = a & hide;
		int temp2 = b & hide;
		if ((temp1 == 0 && temp2 != 0) || (temp2 == 0 && temp1 != 0)) {
			if (!flag)	sum = sum | hide;
		}
		else if (temp1 == 0 && temp2 == 0 && flag) {
			sum = sum | hide;
			flag = false;
		}
		else if (temp1 != 0 && temp2 != 0) {
			if (flag)	sum = sum | hide;
			else		flag = true;
		}
		hide = hide << 1;
	}
	return sum;
}
int pow0(int x, int n) {
	if (n == 0) {
		return 1;
	}
	if (n == 1) {
		return x % 1337;
	}
	return pow0(x % 1337, n / 2) * pow0(x % 1337, n - n / 2) % 1337;
}
int superPow(int a, vector<int>& b) {
	int res = 1;
	for (int i = 0; i < b.size(); ++i) {
		res = pow0(res, 10) * pow0(a, b[i]) % 1337;
	}
	return res;
}
vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
	int len1 = nums1.size(), len2 = nums2.size();
	vector<pair<int, int>> res;
	vector<vector<int>> sums(len1, vector<int>());
	vector<int> locs(len1, 0);
	while (res.size() != k) {
		int temp = INT_MAX, loc = -1;
		for (int i = 0; i != len1; ++i) {
			if (locs[i] != len2 && nums1[i] + nums2[locs[i]] < temp) {
				temp = nums1[i] + nums2[locs[i]];
				loc = i;
			}
		}
		if (loc == -1)	break;
		res.push_back({ nums1[loc], nums2[locs[loc]] });
		++locs[loc];
	}
	return res;
}
class Guess {
public:
	int N;
	int guess(int num) {
		if (N == num)	return 0;
		return N < num ? -1 : 1;
	}
	int guessNumber(int n) {
		int left = 1, right = n, mid;
		while (1) {
			mid = left + (right - left) / 2;
			if (guess(mid) == 0)	return mid;
			guess(mid) == -1 ? right = mid : left = mid + 1;
		}
	}
	int getMoneyAmount(int n) {
		int res = 0, left = 1, right = n, mid;
		while (1) {
			mid = left + (right - left) / 2;
			if (guess(mid) == 0)	break;
			res += mid;
			guess(mid) == -1 ? right = mid : left = mid + 1;
		}
		return res;
	}
};
int wiggleMaxLength(vector<int>& nums) {
	if (nums.empty())	return 0;
	vector<int> up(nums.size(), 0);
	vector<int> down(nums.size(), 0);
	up[0] = down[0] = 1;
	for (int i = 1; i != nums.size(); ++i){
		if (nums[i] > nums[i - 1]){
			up[i] = down[i - 1] + 1;
			down[i] = down[i - 1];
		}
		else if (nums[i] < nums[i - 1]){
			up[i] = up[i - 1];
			down[i] = up[i - 1] + 1;
		}
		else{
			up[i] = up[i - 1];
			down[i] = down[i - 1];
		}
	}
	return max(up.back(), down.back());
}
void helpSum4(vector<int>& nums, int target, int loc, int sum, int& res) {
	if (sum == target)
		++res;
	else if (sum < target) {
		for (int i = loc; i != nums.size(); ++i) {
			helpSum4(nums, target, 0, sum + nums[i], res);
		}
	}
}
int combinationSum04(vector<int>& nums, int target) {
	sort(nums.rbegin(), nums.rend());
	if (nums.back() > target)	return 0;
	int len = nums.size(), res = 0;
	for (int i = 0; i != len; ++i)
		helpSum4(nums, target, 0, nums[i], res);
	return res;
}
int combinationSum4(vector<int>& nums, int target) {
	if (nums.empty())
		return target == 0 ? 1 : 0;
	sort(nums.begin(), nums.end());
	vector<int>dp(target + 1, 0);
	dp[0] = 1;
	for (int i = 1; i <= target; i++) {
		// 这里遍历从i到target的所有值
		for (int j = 0; j<nums.size(); j++) {
			// 这一步叠加生成dp[i]
			if (nums[j] <= i) dp[i] += dp[i - nums[j]];
			else break;
		}
	}
	return dp[target];
}
int kthSmallest(vector<vector<int>>& matrix, int k) {
	int loc = sqrt(k), len = matrix.size();
	if (loc == len)	return matrix.back().back();
	priority_queue<int, vector<int>, greater<int>> hp;
	for (int i = 0; i != loc; ++i) {
		hp.push(matrix[loc][i]);
		hp.push(matrix[i][loc]);
	}
	hp.push(matrix[loc][loc]);
	int kth = k - loc * loc;
	for (int i = 1; i != kth; ++i)
		hp.pop();
	return hp.top();
}
class RandomizedSet {
private:
	vector<int> nums;
	unordered_map<int, int> flag;
public:
	/** Initialize your data structure here. */
	RandomizedSet() {

	}

	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
	bool insert(int val) {
		if (flag.find(val) == flag.end()) {
			nums.push_back(val);
			flag.insert({ val, nums.size() - 1 });
			return true;
		}
		else
			return false;
	}

	/** Removes a value from the set. Returns true if the set contained the specified element. */
	bool remove(int val) {
		if (flag.find(val) != flag.end()) {
			int loc = flag.find(val)->second;
			nums[loc] = nums[nums.size() - 1];
			nums[nums.size() - 1] = val;
			flag.find(nums[loc])->second = loc;
			nums.pop_back();
			flag.erase(val);
			return true;
		}
		else
			return false;
	}

	/** Get a random element from the set. */
	int getRandom() {
		return nums[rand() % nums.size()];
	}
};
class pool {
private:
	ListNode* PHEAD;
public:
	/** @param head The linked list's head.
	Note that the head is guaranteed to be not null, so it contains at least one node. */
	pool(ListNode* head) {
		PHEAD = head;
	}

	/** Returns a random node's value. */
	int getRandom() {
		ListNode* temp = PHEAD;
		int i = 1, res = temp->val;
		while (temp->next) {
			temp = temp->next;
			++i;
			int hot = rand() % i;
			if (hot == 0)
				res = temp->val;
		}
		return res;
	}
};
bool canconstruct(string ransomnote, string magazine) {
	if (ransomnote.empty())	return true;
	if (magazine.empty())	return false;
	unordered_map<char, int> flag;
	int rlen = ransomnote.size(), mlen = magazine.size();
	for (int i = 0; i != mlen; ++i) {
		if (flag.find(magazine[i]) == flag.end())
			flag.insert({ magazine[i], 1 });
		else
			++flag.find(magazine[i])->second;
	}
	for (int i = 0; i != rlen; ++i) {
		if (flag.find(ransomnote[i]) == flag.end())
			return false;
		else if (flag.find(ransomnote[i])->second == 1)
			flag.erase(ransomnote[i]);
		else
			--flag.find(ransomnote[i])->second;
	}
	return true;
}
class Shuf {
private:
	vector<int> initial, temp;
public:
	Shuf(vector<int> nums) {
		initial = nums;
		temp = nums;
	}

	/** Resets the array to its original configuration and return it. */
	vector<int> reset() {
		return initial;
	}

	/** Returns a random shuffling of the array. */
	vector<int> shuffle() {
		temp.clear();
		vector<int> flag;
		for (int num : initial)
			flag.push_back(num);
		while (!flag.empty()) {
			int loc = rand() % flag.size();
			int tmp = flag.back();
			flag[flag.size() - 1] = flag[loc];
			flag[loc] = tmp;
			temp.push_back(flag.back());
			flag.pop_back();
		}
		return temp;
	}
};
void helper(vector<int>&work, int n, int sum) {
	for (int i = 0; i <= 9; ++i) {
		int tmp = sum + i;
		if (tmp <= n) {
			work.push_back(tmp);
			helper(work, n, tmp * 10);
		}
		else {
			break;
		}
	}
	return;
}
vector<int> lexicalOrder(int n) {
	vector<int>work;
	for (int i = 1; i <= 9; ++i) {
		if (i <= n) {
			work.push_back(i);
			helper(work, n, i * 10);
		}
		else {
			break;
		}
	}
	return work;
}
int firstUniqChar(string s) {
	unordered_map<char, int> flag;
	for (char temp : s) {
		if (flag.find(temp) == flag.end())
			flag.insert({ temp, 1 });
		else
			++flag.find(temp)->second;
	}
	int len = s.size();
	for (int i = 0; i != len; ++i) {
		if (flag.find(s[i])->second == 1)
			return i;
	}
	return -1;
}
char findTheDifference(string s, string t) {
	if (s.empty())	return t[0];
	int slen = s.size();
	char temp = s[0] ^ t[0];
	for (int i = 1; i != slen; ++i)
		temp = temp ^ s[i] ^ t[i];
	temp = temp ^ t.back();
	return temp;
}
bool isSubsequence(string s, string t) {
	if (s.empty())	return true;
	int slen = s.size(), tlen = t.size();
	int sloc = 0, tloc = 0;
	while (tloc != tlen) {
		if (s[sloc] == t[tloc])
			++sloc;
		if (sloc == slen)	return true;
		++tloc;
	}
	return false;
}
int helpUtf8(int num) {
	int flag = 128, res = 0;
	for (int i = 0; i != 8; ++i) {
		if (flag & num) {
			++res;
			flag = flag >> 1;
		}
		else break;
	}
	return res;
}
bool validUtf8(vector<int>& data) {
	if (data.empty())	return true;
	int L = data.size(), i = 0;
	while (i < L) {
		int len = helpUtf8(data[i]);
		if (len == 1 || len > 4)
			return false;
		if (len != 0) {
			if (L - i < len)
				return false;
			for (int j = 1; j != len; ++j) {
				if (helpUtf8(data[i + j]) != 1)
					return false;
			}
			i += len;
		}
		else			//len == 0
			++i;
	}
	return true;
}
string decodeString(string s) {
	if (s.empty())	return {};
	stack<int> num;
	stack<string> words;
	string res;
	int len = s.size();
	for (int i = 0; i != len; ++i) {
		if (isalpha(s[i]))
			res.push_back(s[i]);
		else if (s[i] >= '0' && s[i] <= '9') {
			words.push(res);
			res.clear();
			int j = i + 1;
			while (s[j] != '[')	++j;
			num.push(atoi(s.substr(i, j - i).c_str()));
			i = j;
		}
		else if (s[i] == ']') {
			string temp = res;
			for (int i = 0; i != num.top() - 1; ++i)
				res += temp;
			res = words.top() + res;
			words.pop();
			num.pop();
		}
	}
	return res;
}
int helpSubstring(vector<int> lwords, vector<int> rwords) {
	int res = INT_MAX;
	for (int i = 0; i != 26; ++i) {
		if ((rwords[i] - lwords[i]) && (rwords[i] - lwords[i]) < res)
			res = rwords[i] - lwords[i];
	}
	return res;
}
int longestSubstring0(string s, int k) {
	if (s.empty())	return 0;
	int len = s.size();
	if (k <= 1)	return len;
	vector<vector<int>> flag;
	vector<int> words(26, 0);
	flag.push_back(words);
	for (int i = 1; i != len + 1; ++i) {
		++words[s[i - 1] - 'a'];
		flag.push_back(words);
	}
	for (int i = len; i != k - 1; --i) {
		for (int j = 0; i + j != len + 1; ++j) {
			if (helpSubstring(flag[j], flag[i + j]) >= k)
				return i;
		}
	}
	return 0;
}
int longestSubstring(string s, int k) {
	if (k <= 1)	return s.size();
	if (s.size() < k)	return 0;
	unordered_map<char, int> work;
	for (auto i : s)
		++work[i];
	bool flag = true;
	for (auto i : work) {
		if (i.second < k)
			flag = false;
	}
	if (flag == true)
		return s.size();
	int pre = 0;
	int maxLen = 0;
	int i = 0;
	for (; i<s.size(); ++i) {
		if (work[s[i]] < k) {
			maxLen = max(maxLen, longestSubstring(s.substr(pre, i - pre), k));
			pre = i + 1;
		}
	}
	maxLen = max(maxLen, longestSubstring(s.substr(pre, i - pre), k));
	return maxLen;
}
int maxRotateFunction(vector<int>& A) {
	int len = A.size();
	int res = INT_MIN, temp = 0;
	for (int i = 0; i != len; ++i) {
		for (int j = 0; j != len; ++j) {
			temp += j * A[(j + i) % len];
		}
		if (temp > res)
			res = temp;
		temp = 0;
	}
	return res;
}
int bitnum(int num) {
	int temp = num, res = 0, hide = 1;
	while(temp) {
		if (temp & hide)
			++res;
		temp >>= 1;
	}
	return res;
}
int integerReplacement(int n) {
	int res = 0;
	while (n != 1) {
		if (n % 2) {
			int temp1 = n + 1, temp2 = n - 1;
			int bnum1 = bitnum(temp1), bnum2 = bitnum(temp2);
			n = bnum1 < bnum2 ? temp1 : temp2;
		}
		else
			n /= 2;
		++res;
	}
	return res;
}
class Index {
/*
private:
	vector<int> N;
public:
	Index(vector<int> nums) {
		N = nums;
	}

	int pick(int target) {
		int len = N.size(), res = 0, flag = 1;
		for (int i = 0; i != len; ++i) {
			if (N[i] == target && rand() % (flag++) == 0)
				res = i;
		}
		return res;
	}
*/
private:
	unordered_map<int, vector<int>> loclist;
public:
	Index(vector<int> nums) {
		int len = nums.size();
		for (int i = 0; i != len; ++i)
			loclist[nums[i]].push_back(i);
	}

	int pick(int target) {
		int len = loclist[target].size();
		return loclist[target][rand() % len];
	}
};
int findNthDigit(int n) {
	if (n < 10)	return n;
	int bitnum = 1;
	while (n - 9 * pow(10, bitnum - 1) * bitnum > 0) {
		n -= 9 * pow(10, bitnum - 1) * bitnum;
		++bitnum;
	}
	int num = pow(10, bitnum - 1) + (n - 1) / bitnum;
	int res = 0;
	for (int i = (n - 1) % bitnum; i != bitnum; ++i) {
		res = num % 10;
		num /= 10;
	}
	return res;
}
void helpWatchHour(int num, int temp, int loc, vector<string>& hours) {
	if (num == 0) {
		if(temp < 12)
			hours.push_back(to_string(temp));
	}
	else {
		for (int i = loc; i <= 4 - num; ++i) {
			int flag = 1 << i;
			int his = temp;
			temp |= flag;
			helpWatchHour(num - 1, temp, i + 1, hours);
			temp = his;
		}
	}
}
void helpWatchMinute(int num, int temp, int loc, vector<string>& minutes) {
	if (num == 0) {
		if(temp < 60)
			minutes.push_back(temp < 10 ? ("0" + to_string(temp)) : to_string(temp));
	}
	else {
		for (int i = loc; i <= 6 - num; ++i) {
			int flag = 1 << i;
			int his = temp;
			temp |= flag;
			helpWatchMinute(num - 1, temp, i + 1, minutes);
			temp = his;
		}
	}
}
vector<string> readBinaryWatch(int num) {
	vector<string> res;
	for (int i = 0; i <= min(3, num); ++i) {
		if (num - i > 6)	continue;
		vector<string> hours, minutes;
		helpWatchHour(i, 0, 0, hours);
		helpWatchMinute(num - i, 0, 0, minutes);
		for (int m = 0; m != hours.size(); ++m) {
			for (int n = 0; n != minutes.size(); ++n)
				res.push_back(hours[m] + ":" + minutes[n]);
		}
	}
	return res;
}
string removeKdigits(string num, int k) {
	int len = num.size();
	if (len == k)	return "0";
	string res;
	res.push_back(num[0]);
	for (int i = 1; i != len; ++i) {
		while (!res.empty() && num[i] < res.back() && k != 0) {
			--k;
			res.pop_back();
		}
		res.push_back(num[i]);
	}
	for (int i = 0; i != k; ++i)
		res.pop_back();
	int loc = -1;
	while (res[++loc] == '0');
	return res.substr(loc).empty() ? "0" : res.substr(loc);
}
int sumOfLeftLeaves(TreeNode* root) {
	if (!root)	return 0;
	queue<TreeNode*> qe;
	qe.push(root);
	TreeNode* temp = root;
	int res = 0;
	while (!qe.empty()) {
		if (temp) {
			if (temp->left) {
				if (!temp->left->left && !temp->left->right)
					res += temp->left->val;
				else
					qe.push(temp->left);
			}
			if (temp->right)
				qe.push(temp->right);
		}
		qe.pop();
		if(!qe.empty())
			temp = qe.front();
	}
	return res;
}
string toHex(int num) {
	if (num == 0)	return "0";
	int flag = 0x0000000F;
	string res = "00000000";
	for (int i = 0; i != 8; ++i) {
		int temp = flag & num;
		res[7 - i] = temp < 10 ? temp + '0' : temp - 10 + 'a';
		num >>= 4;
	}
	int loc = res.find_first_not_of('0');
	return res.substr(loc);
}
int longestPalindrome(string s) {
	if (s.empty())  return 0;
	unordered_map<char, int> flag;
	for (char temp : s)
		flag[temp] += 1;
	int snum = 0, res = 0;
	for (auto temp : flag) {
		if (temp.second % 2)
			++snum;
		res += temp.second;
	}
	return res - snum + 1;
}
vector<string> fizzBuzz(int n) {
	if (n < 1)	return {};
	vector<string> res(n, "");
	for (int i = 0; i != n; ++i) {
		if ((i + 1) % 3 == 0) {
			res[i] += "Fizz";
			if ((i + 1) % 5 == 0)
				res[i] += "Buzz";
		}
		else if ((i + 1) % 5 == 0)
			res[i] += "Buzz";
		else
			res[i] = to_string(i + 1);
	}
	return res;
}
bool helpArithmeticSlicesv(vector<int>& A, int loc) {
	return (A[loc + 1] - A[loc] == A[loc + 2] - A[loc + 1]);
}
int	fac(int num) {
	int res = num;
	while (num != 1)
		res += (--num);
	return res;
}
int numberOfArithmeticSlices(vector<int>& A) {
	int len = A.size();
	if (len < 3)	return 0;
	int i = 0, res = 0;
	while (i + 2 < len) {
		if (helpArithmeticSlicesv(A, i)) {
			int ASlen = 2, ASdim = A[i + 1] - A[i];
			while (i + ASlen + 1 < len && A[i + ASlen + 1] - A[i + ASlen] == ASdim)
				++ASlen;
			i += ASlen;
			res += fac(ASlen - 1);
		}
		else
			++i;
	}
	return res;
}
int thirdMax(vector<int>& nums) {
	int len = nums.size();
	if (len < 3) {
		return len == 1 ? nums[0] : max(nums[0], nums[1]);
	}
	set<int> res;
	int i = 0, line = INT_MAX;
	while (i != len) {
		if (nums[i] < line)
			line = nums[i];
		res.insert(nums[i++]);
		if (res.size() == 3)
			break;
	}
	while (i != len) {
		if (nums[i] > line && res.find(nums[i]) == res.end()) {
			res.erase(line);
			res.insert(nums[i]);
			int newline = INT_MAX;
			for (auto temp : res)
				if (temp < newline)
					newline = temp;
			line = newline;
		}
		++i;
	}
	return res.size() == 3 ? *res.begin() : *(--res.end());
}
string addStrings(string num1, string num2) {
	int len = min(num1.size(), num2.size());
	int len0 = max(num1.size(), num2.size());
	int flag = 0;
	string res(len, 0);
	int i = 0;
	while (i != len) {
		char temp = num1[num1.size() - 1 - i] + num2[num2.size() - 1 - i] + flag - '0';
		if (temp > '9') {
			temp -= 10;
			flag = 1;
		}
		else
			flag = 0;
		res[len - i - 1] = temp;
		++i;
	}
	if (num1.size() == num2.size())
		return flag ? "1" + res : res;
	string res0 = (num1.size() > num2.size() ? num1.substr(0, num1.size() - i) : num2.substr(0, num2.size() - i)) + res;
	if (!flag)	return res0;
	else 
		while (i != len0 && flag) {
			if (res0[len0 - 1 - i] == '9')
				res0[len0 - 1 - i] = '0';
			else {
				res0[len0 - 1 - i] += 1;
				flag = 0;
				break;
			}
			++i;
		}
	return (i == len0 && flag) ? "1" + res0 : res0;
}
bool canPartition(vector<int>& nums) {
	int sum = 0, len = nums.size();
	for (int temp : nums)
		sum += temp;
	if (sum & 1)	return false;
	sum /= 2;
	vector<vector<bool>> flag(len, vector<bool>(sum + 1, false));
	flag[0][nums[0]] = true;
	for (int i = 0; i != len; ++i)
		flag[i][0] = true;
	for (int i = 1; i != len; ++i) {
		for (int j = 1; j <= sum; ++j)
			flag[i][j] = flag[i - 1][j] || (j - nums[i] >= 0 ? flag[i - 1][j - nums[i]] : false);
	}
	return flag[len - 1][sum];
}
void helpBattleships(vector<vector<char>>& board, int row, int col, int i, int j) {
	board[i][j] = 'O';
	int loc = 1;
	while (i + loc < row && board[i + loc][j] == 'X')
		board[i + loc++][j] = 'O';
	loc = 1;
	while (j + loc < col && board[i][j + loc] == 'X')
		board[i][j + loc++] = 'O';
}
int countBattleships(vector<vector<char>>& board) {
	int row = board.size(), col = board[0].size();
	int count = 0;
	for (int i = 0; i != row; ++i) {
		for (int j = 0; j != col; ++j) {
			if (board[i][j] == 'X') {
				helpBattleships(board, row, col, i, j);
				++count;
			}
		}
	}
	return count;
}
int findMaximumXOR(vector<int>& nums) {
	int max = 0, mask = 0;
	for (int i = 31; i >= 0; i--) {
		set<int> set;
		mask = mask | (1 << i);
		for (int num : nums) {
			set.insert(num & mask);
		}
		int temp = max | (1 << i);
		for (int element : set) {
			if (set.find(element ^ temp) != set.end()) {
				max = temp;
				break;
			}
		}
	}
	return max;
}
int characterReplacement(string s, int k) {
	if (s.empty())	return 0;
	int len = s.size();
	unordered_map<char, int> alpha;
	vector<vector<int>> flag(len, vector<int>(len, 1));
	for (int i = 0; i != len; ++i) {
		++alpha[s[i]];
		for (auto temp : alpha)
			if (temp.second > flag[0][i])
				flag[0][i] = temp.second;
	}
	for (int i = 1; i != len; ++i) {
		--alpha[s[i - 1]];
		auto tempalpha = alpha;
		for (int j = len - 1; j != i - 1; --j) {
			for (auto temp : tempalpha)
				if (temp.second > flag[i][j])
					flag[i][j] = temp.second;
			--tempalpha[s[j]];
		}
	}
	int res = 0;
	for (int i = 0; i != len; ++i) {
		for (int j = i; j != len; ++j) {
			if (j - i + 1 - flag[i][j] <= k && j - i + 1 > res)
				res = j - i + 1;
		}
	}
	return res;
}
class Node {
public:
	bool val;
	bool isLeaf;
	Node* topLeft;
	Node* topRight;
	Node* bottomLeft;
	Node* bottomRight;

	Node() {}

	Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = _topLeft;
		topRight = _topRight;
		bottomLeft = _bottomLeft;
		bottomRight = _bottomRight;
	}
};
void helpContruct(Node* head, vector<vector<int>>& grid, int row, int col, int len) {
	int temp = grid[row][col], i, j;
	for (i = row; i != row + len; ++i) {
		for (j = col; j != col + len; ++j) {
			if (grid[i][j] != temp)
				break;
			temp = grid[i][j];
		}
		if (j != col + len)
			break;
	}
	if (i == row + len && j == col + len) {
		head->isLeaf = true;
		head->val = temp;
	}
	else {
		head->isLeaf = false;
		Node *topLeft = new Node(0, true, nullptr, nullptr, nullptr, nullptr);
		Node *topRight = new Node(0, true, nullptr, nullptr, nullptr, nullptr);
		Node *bottomLeft = new Node(0, true, nullptr, nullptr, nullptr, nullptr);
		Node *bottomRight = new Node(0, true, nullptr, nullptr, nullptr, nullptr);
		head->topLeft = topLeft;
		head->topRight = topRight;
		head->bottomLeft = bottomLeft;
		head->bottomRight = bottomRight;
		helpContruct(topLeft, grid, row, col, len / 2);
		helpContruct(topRight, grid, row, col + len / 2, len / 2);
		helpContruct(bottomLeft, grid, row + len / 2, col, len / 2);
		helpContruct(bottomRight, grid, row + len / 2, col + len / 2, len / 2);
	}
}
Node* construct(vector<vector<int>>& grid) {
	int len = grid.size();
	Node* head = new Node(0, true, nullptr, nullptr, nullptr, nullptr);
	helpContruct(head, grid, 0, 0, len);
	return head;
}
class Node0 {
public:
	int val = NULL;
	vector<Node0*> children;

	Node0() {}

	Node0(int _val, vector<Node0*> _children) {
		val = _val;
		children = _children;
	}
};
vector<vector<int>> levelOrder(Node0* root) {
	if (!root)	return {};
	vector<vector<int>> res;
	queue<Node0*> qe;
	int num = 1, nextnum = 0;
	Node0* temp = root;
	qe.push(temp);
	while (temp) {
		vector<int> tempres;
		while (num) {
			tempres.push_back(temp->val);
			nextnum += temp->children.size();
			for (auto chdr : temp->children)
				qe.push(chdr);
			qe.pop();
			temp = qe.empty() ? nullptr : qe.front();
			--num;
		}
		res.push_back(tempres);
		num = nextnum;
		nextnum = 0;
	}
	return res;
}
class Node1 {
public:
	int val = NULL;
	Node1* prev = NULL;
	Node1* next = NULL;
	Node1* child = NULL;

	Node1() {}

	Node1(int _val, Node1* _prev, Node1* _next, Node1* _child) {
		val = _val;
		prev = _prev;
		next = _next;
		child = _child;
	}
};
Node1* flatten(Node1* head) {
	if (!head)	return head;
	stack<Node1*> st;
	st.push(head);
	Node1 *res = new Node1(), *temp, *behind;
	behind = res;
	while (1) {
		temp = st.top();
		st.pop();
		behind->next = temp;
		temp->prev = behind;
		while (temp) {
			if (temp->child) {
				st.push(temp->next);
				temp->next = temp->child;
				temp->child = nullptr;
				temp->next->prev = temp;
			}
			behind = temp;
			temp = temp->next;
		}
		if (st.empty())	break;
	}
	return res->next;
}
int helpminMutation(const string& start, const string& target) {  //找出两字符串不同字符数
	if (start.size() != target.size())	return -1;  //长度不同直接返回-1，表示无法匹配
	int len = start.size(), res = 0;
	for (int i = 0; i != len; ++i) {
		if (start[i] != target[i])
			++res;
	}
	return res;
}
int dfsMinMutation(const vector<vector<bool>>& flag, int start, int tar) {  //BFS找出最小层数
	unordered_set<int> his;  //存储已访问过的字符串
	int len = flag.size(), res = 0, templen = 1;
	queue<int> floor;
	floor.push(start);  //
	his.insert(start);  //循环前准备工作
	while (!floor.empty()) {  //与之前的分层层序遍历相同
		while (templen != 0) {
			int temp = floor.front();
			floor.pop();
			if (temp == tar)	return res;  //BFS到达目标字符串，直接返回当前层数
			for (int i = 0; i != len; ++i) {
				if (flag[temp][i] && !his.count(i)) {
					floor.push(i);
					his.insert(i);
				}
			}
			--templen;
		}
		++res;
		templen = floor.size();
	}
	return -1;   //未找到，返回-1
}
//做的时候没有将初始字符串存入bank中，而是分别查找bank中与初始字符串完全相同或相差一个字符的字符串，应该是有点麻烦了，可以直接将初始字符串存入bank中
int minMutation(string start, string end, vector<string>& bank) {
	if (start.size() != end.size())	return -1;
	int len = start.size(), nums = bank.size();
	unordered_map<int, vector<int>> step;  //此处分别存储bank中与初始字符串相同以及相差一个字符的字符串的位置，用vector更方便，可以再优化一下。
	vector<vector<bool>> flag(nums, (vector<bool>(nums, false))); //标记bank中各个字符串之间是否相差一个字符，相差一个的为true，相同或大于1的为false。
	for (int i = 0; i != nums; ++i) {  //将bank中与start相同或相差一个的存入step中
		int tempstep = helpminMutation(start, bank[i]);
		if (tempstep <= 1)
			step[tempstep].push_back(i);
	}
	if (step.empty())	return -1;  //没找到，无法转换
	int tar = -1; //查找目标字符串位置
	for (int i = 0; i != nums; ++i) {
		if (i == nums)	return -1;
		int tempstep = helpminMutation(end, bank[i]);
		if (tempstep == 0) {
			tar = i;
			break;
		}
	}
	if (tar == -1)	return -1; //没找到，返回-1
	for (int i = 0; i != nums; ++i) {  //判断bank中各个字符串间的关系，存入flag中
		if (bank[i].size() != len)	continue;
		for (int j = i + 1; j != nums; ++j) {
			if (helpminMutation(bank[i], bank[j]) == 1) {
				flag[i][j] = true;  //无向图，[i][j]和[j][i]都应该置true
				flag[j][i] = true;
			}
		}
	}
	int res = INT_MAX;
	for (auto s : step) {
		for (int i = 0; i != s.second.size(); ++i) {
			int tempres = dfsMinMutation(flag, s.second[i], tar); //从与start相同的或相差一个字符的字符串开始进行BFS
			if (tempres != -1 && tempres + s.first < res)  //注意需要加s.first，first存储的是与start字符串相差的字符数，只能是0或1
				res = tempres + s.first;
		}
	}
	return res == INT_MAX ? -1 : res;  //若res仍为INT_MAX，表示未找到路径，返回-1
}
int countSegments(string s) {
	if (s.empty())   return 0;
	int len = s.size(), head = s.find_first_not_of(" ");
	if (head == -1)   return 0;
	int res = 0;
	for (int i = s.find_first_not_of(" "); i != len; ++i) {
		if (s[i] != ' ') continue;
		else {
			++res;
				while (i != len && s[i] == ' ')
					++i;
			--i;
		}
	}
	return s[len - 1] == ' ' ? res : res + 1;
}
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};
int helpEraseOI(const vector<int>& overNums) {
	int loc = -1, res = 0;
	for (int i = 0; i != overNums.size(); ++i) {
		if (overNums[i] > res) {
			loc = i;
			res = overNums[i];
		}
	}
	return loc;
}
int eraseOverlapIntervals(vector<Interval>& intervals) {
	if (intervals.empty())	return 0;
	int len = intervals.size();
	vector<int> overNums(len, 0);
	unordered_map<int, vector<int>> overLocs;
	for (int i = 0; i != len; ++i) {
		for (int j = i + 1; j != len; ++j) {
			if (intervals[j].start < intervals[i].start && intervals[j].end > intervals[i].start
				|| intervals[j].start < intervals[i].end && intervals[j].end > intervals[i].end
				|| intervals[j].start >= intervals[i].start && intervals[j].end <= intervals[i].end) {
				++overNums[i];
				++overNums[j];
				overLocs[i].push_back(j);
				overLocs[j].push_back(i);
			}
		}
	}
	int maxloc = helpEraseOI(overNums), res = 0;
	while (maxloc != -1) {
		for (int i = 0; i != overLocs[maxloc].size(); ++i)
			--overNums[overLocs[maxloc][i]];
		overNums[maxloc] = 0;
		++res;
		maxloc = helpEraseOI(overNums);
	}
	return res;
}
int helpFindRight(const vector<int>& starts, int end) {
	int len = starts.size();
	int left = 0, right = len - 1;
	while (left < right) {
		int mid = (right - left) / 2 + left;
		if (starts[mid] == end)	return mid;
		if (starts[mid] > end)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return starts[right] >= end ? right : right + 1;
}
vector<int> findRightInterval(vector<Interval>& intervals) {
	if (intervals.empty())	return {};
	int len = intervals.size();
	if (len == 1)	return { -1 };
	unordered_map<int, int> flags;
	for (int i = 0; i != len; ++i)
		flags[intervals[i].start] = i;
	vector<int> starts;
	for (auto temp : flags)
		starts.push_back(temp.first);
	sort(starts.begin(), starts.end());
	vector<int> res;
	for (int i = 0; i != len; ++i) {
		if (intervals[i].end > starts.back())
			res.push_back(-1);
		else {
			int st = helpFindRight(starts, intervals[i].end);
			res.push_back(flags[starts[st]]);
		}
	}
	return res;
}
bool helpFindAnagrams(const vector<int>& flag, const vector<int>& temp) {
	for (int i = 0; i != 26; ++i) {
		if (flag[i] != temp[i])
			return false;
	}
	return true;
}
vector<int> findAnagrams(string s, string p) {
	int lim = s.size(), len = p.size();
	if (lim < len)	return {};
	vector<int> flag(26, 0), temp(26, 0), res;
	int loc = 0;
	while(loc != len) {
		++temp[s[loc] - 'a'];
		++flag[p[loc] - 'a'];
		++loc;
	}
	while (loc != lim) {
		if (helpFindAnagrams(flag, temp))
			res.push_back(loc - len);
		--temp[s[loc - len] - 'a'];
		++temp[s[loc] - 'a'];
		++loc;
	}
	if (helpFindAnagrams(flag, temp))
		res.push_back(loc - len);
	return res;
}
void helpFindKthNumber(long long& num, long long& res, int n, int k, long long sum) {
	for (int i = 0; i <= 9; ++i) {
		long long tmp = sum + i;
		if (tmp <= n) {
			++num;
			if (num == k) {
				res = tmp;
				return;
			}
			else if (num > k)
				return;
			helpFindKthNumber(num, res, n, k, tmp * 10);
		}
		else break;
	}
	return;
}
int findKthNumber(int n, int k) {
	long long num = 0, res = 0;
	for (int i = 1; i <= 9; ++i) {
		if (i <= n) {
			++num;
			if (num == k)	return i;
			helpFindKthNumber(num, res, n, k, i * 10);
		}
		else break;
	}
	return res;
}
int arrangeCoins(int n) {
	int i = 1;
	while (n < i) {
		n -= i;
		++i;
	}
	return i;
}
vector<int> findDuplicates(vector<int>& nums) {
	int len = nums.size(), loc = 0;
	while (loc != len) {
		if (nums[loc] != nums[nums[loc] - 1]) {
			int temp = nums[nums[loc] - 1];
			nums[nums[loc] - 1] = nums[loc];
			nums[loc] = temp;
		}
		else
			++loc;
	}
	vector<int> res;
	for (int i = 0; i != len; ++i) {
		if (nums[i] != i + 1)
			res.push_back(nums[i]);
	}
	return res;
}
int compress(vector<char>& chars) {
	if (chars.empty())	return 0;
	int left = chars.size() - 1, right = chars.size() - 1;
	while (left != -1) {
		char temp = chars[right];
		int times = 0;
		while (left != -1 && chars[left] == temp) {
			++times;
			--left;
		}
		if (times > 2) {
			chars.erase(chars.begin() + (left + 2), chars.begin() + (left + 2 + times - 1));
			vector<char> tm;
			while (times != 0) {
				int bit = times % 10;
				tm.push_back(bit + '0');
				times /= 10;
			}
			chars.insert(chars.begin() + left + 2, tm.rbegin(), tm.rend());
		}
		else if (times == 2)
			chars[left + 2] = '2';
		right = left;
	}
	return chars.size();
}
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	if (!l1)	return l2;
	if (!l2)	return l1;
	stack<ListNode*> st1, st2, st;
	st.push(nullptr);
	ListNode *temp1 = l1, *temp2 = l2;
	while (l1) {
		st1.push(l1);
		l1 = l1->next;
	}
	while (l2) {
		st2.push(l2);
		l2 = l2->next;
	}
	int flag = 0, lim = min(st1.size(), st2.size());
	for (int i = 0; i != lim; ++i) {
		int tempnum = st1.top()->val + st2.top()->val + flag;
		if (tempnum > 9) {
			tempnum -= 10;
			flag = 1;
		}
		else
			flag = 0;
		ListNode* temp = new ListNode(tempnum);
		temp->next = st.top();
		st.push(temp);
		st1.pop();
		st2.pop();
	}
	if (st1.empty() && !st2.empty()) { 
		while (!st2.empty()) {
			int tempnum = st2.top()->val + flag;
			if (tempnum == 10) {
				tempnum = 0;
				flag = 1;
			}
			else
				flag = 0;
			ListNode* temp = new ListNode(tempnum);
			temp->next = st.top();
			st.push(temp);
			st2.pop();
		}
	}
	else if (!st1.empty() && st2.empty()){
		while (!st1.empty()) {
			int tempnum = st1.top()->val + flag;
			if (tempnum == 10) {
				tempnum = 0;
				flag = 1;
			}
			else
				flag = 0;
			ListNode* temp = new ListNode(tempnum);
			temp->next = st.top();
			st.push(temp);
			st1.pop();
		}
	}
	if (flag) {
		ListNode* temp = new ListNode(1);
		temp->next = st.top();
		return temp;
	}
	return st.top();
}
int helpBoomerrangs(pair<int, int> a, pair<int, int> b) {
	return (a.first - b.first)*(a.first - b.first)
		+ (a.second - b.second)*(a.second - b.second);
}
int numberOfBoomerangs(vector<pair<int, int>>& points) {
	if (points.empty())	return 0;
	int len = points.size();
	int res = 0;
	for (int i = 0; i != len; ++i) {
		unordered_map<int, int> length;
		for (int j = i + 1; j != len; ++j) {
			int temp = helpBoomerrangs(points[i], points[j]);
			++length[temp];
		}
		for (auto item : length)
			res += item.second * (item.second - 1);
	}
	return res;
}
vector<int> findDisappearedNumbers(vector<int>& nums) {
	int len = nums.size(), loc = 0;
	while (loc != len) {
		if (nums[loc] == loc + 1 || nums[loc] == nums[nums[loc] - 1]) {
			++loc;
		}
		else {
			int temp = nums[loc];
			nums[loc] = nums[nums[loc] - 1];
			nums[temp - 1] = temp;
		}
	}
	vector<int> res;
	for (int i = 0; i != len; ++i) {
		if (nums[i] != i + 1)
			res.push_back(i + 1);
	}
	return res;
}
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		if (!root)	return "";
		stack<TreeNode*> st;
		TreeNode* temp = root;
		string res;
		while (temp || !st.empty()) {
			while (temp) {
				res += (to_string(temp->val) + ' ');
				st.push(temp);
				temp = temp->left;
			}
			if (!st.empty()) {
				temp = st.top()->right;
				st.pop();
			}
			else
				temp = nullptr;
		}
		return res;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		int slen = data.size(), temploc = 0;
		vector<TreeNode*> nums;
		while (temploc != slen) {
			int tempnum = 0;
			while (data[temploc] != ' ')
				tempnum = tempnum * 10 + data[temploc++] - '0';
			nums.push_back(new TreeNode(tempnum));
			++temploc;
		}
		TreeNode* head = new TreeNode(INT_MAX);
		stack<TreeNode*> st;
		st.push(head);
		int loc = 0, len = nums.size();
		while (loc != len) {
			if (nums[loc]->val < st.top()->val) {
				st.top()->left = nums[loc];
				st.push(nums[loc]);
				++loc;
			}
			else {
				TreeNode* temp = st.top();
				st.pop();
				while (nums[loc]->val > st.top()->val) {
					temp = st.top();
					st.pop();
				}
				temp->right = nums[loc];
				st.push(nums[loc]);
				++loc;
			}
		}
		return head->left;
	}
};
TreeNode* deleteNode(TreeNode* root, int key) {
	if (!root)	return nullptr;
	TreeNode* anc = new TreeNode(INT_MIN);
	anc->right = root;
	TreeNode* found = root, *head = anc;
	while (found) {
		if (found->val == key)
			break;
		else {
			anc = found;
			if (found->val < key)
				found = found->right;
			else
				found = found->left;
		}
	}
	if (!found)	return root;
	TreeNode* temp = found;
	while (temp->left) {
		anc = temp;
		temp = temp->left;
	}
	found->val = temp->val;
	temp->val = key;
	found = temp;
	while (temp->right) {
		anc = temp;
		temp = temp->right;
		while (temp->left) {
			anc = temp;
			temp = temp->left;
		}
		found->val = temp->val;
		temp->val = key;
		found = temp;
	}
	(anc->left && anc->left->val == key) ? 
		anc->left = nullptr : anc->right = nullptr;
	return head->right;
}
string frequencySort(string s) {
	unordered_map<char, int> times;
	int len = s.size();
	for (char word : s)
		++times[word];
	map<int, vector<char>> flags;
	for (pair<char, int> temp : times)
		flags[temp.second].push_back(temp.first);
	int loc = 0;
	for (pair<int, vector<char>> temp : flags) {
		for (int i = 0; i != temp.second.size(); ++i) {
			for (int m = len - 1 - loc; m != len - 1 - loc - temp.first; --m) {
				s[m] = temp.second[i];
			}
			loc += temp.first;
		}
	}
	return s;
}

static bool helpFindMin(pair<int, int>& A, pair<int, int>& B) {
	return A.first<B.first;
}
int findMinArrowShots(vector<pair<int, int>>& points) {
	if (points.empty()) return 0;
	sort(points.begin(), points.end(), helpFindMin);
	int end = points[0].second, res = 0;
	for (int i = 0; i != points.size(); ++i) {
		if (points[i].first > end) {
			++res;
			end = points[i].second;
		}
		else {
			end = min(points[i].second, end);
		}

	}
	return res == -1 ? res = 1 : ++res;
}
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
	unordered_map<int, int> flag;
	for (int i = 0; i != A.size(); ++i) {
		for (int j = 0; j != B.size(); ++j)
			++flag[A[i] + B[j]];
	}
	int res = 0;
	for (int m = 0; m != C.size(); ++m) {
		for (int n = 0; n != D.size(); ++n) {
			if (flag.count(0 - C[m] - D[n]))
				res += flag[0 - C[m] - D[n]];
		}
	}
	return res;
}
int findContentChildren(vector<int>& g, vector<int>& s) {
	sort(g.begin(), g.end());
	map<int, int> s0;
	for (int temp : s)
		++s0[temp];
	int res = 0;
	for (int i = g.size() - 1; i != -1; --i) {
		if (s0.empty())	break;
		if (s0.lower_bound(g[i]) != s0.end()) {
			++res;
			int bis = s0.lower_bound(g[i])->first;
			int num = --s0[bis];
			if (num == 0)
				s0.erase(bis);
		}
	}
	return res;
}
bool find132pattern(vector<int>& nums) {
	int len = nums.size();
	if (len < 3)	return false;
	int head = nums[0], mid = nums[0];
	for (int i = 1; i != len; ++i) {
		if (nums[i] < head) {
			if (mid > head)	return true;
			else
				head = mid = nums[i];
		}
		else if (nums[i] >= head && nums[i] < mid)
			return true;
		else
			mid = nums[i];
	}
	return false;
}
bool helpArrayLoop(int num) {
	return num > 0 ? true : false;
}
bool circularArrayLoop(vector<int>& nums) {
	int len = nums.size();
	if (len < 2)	return false;
	int head = 0, loc = 0, time = 0, size = 1;
	bool flag = helpArrayLoop(nums[loc]);
	while (time != len) {
		if (helpArrayLoop(nums[loc]) != flag) {
			flag = helpArrayLoop(nums[loc]);
			head = loc;
			size = 1;
		}
		int mov = (loc + nums[loc]) % len;
		loc = mov >= 0 ? mov : len + mov;
		if (loc == head && size > 1)	return true;
		++size;
		++time;
	}
	return false;
}
int helpPoorPigs(int toDiv, int div) {
	return toDiv % div == 0 ? toDiv / div : toDiv / div + 1;
}
int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
	return helpPoorPigs(buckets, helpPoorPigs(minutesToTest, minutesToDie));
}
bool repeatedSubstringPattern(string s) {
	int len = s.size();
	char head = s[0];
	vector<int> locs;
	for (int i = 1; i != len; ++i) {
		if (s[0] == head)
			locs.push_back(i);
	}
	if (locs.empty())	return false;
	int locsNum = 0;
	string son = s.substr(0, locs[locsNum]);
	while (son.size() <= len / 2) {
		if (len % son.size() == 0) {
			int times = 1;
			while (locs[locsNum] * times < len) {
				if (son != s.substr(locs[locsNum] * times, son.size()))
					break;
				++times;
			}
			if (locs[locsNum] * times == len)
				return true;
		}
		if ((++locsNum) == locs.size())
			return false;
		son = s.substr(0, locs[locsNum]);
	}
	return false;
}
float sum(float a[], unsigned len) {
	int i;
	float res = 0;
	for (i = 0; i <= len - 1; i++)
		res += a[i];
	return res;
}
int hammingDistance(int x, int y) {
	int temp = x ^ y, res = 0;
	while (temp != 0) {
		res += 1 & temp;
		temp >>= 1;
	}
	return res;
}
int minMoves2(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	int mid = nums[nums.size() / 2], res = 0;
	for (int temp : nums)
		res += abs(temp - mid);
	return res;
}
int helpIslandPerimeter(vector<vector<int>>& grid, int i, int j) {
	int res = 0;
	if (grid[i][j - 1] == 0)	++res;
	if (grid[i][j + 1] == 0)	++res;
	if (grid[i - 1][j] == 0)	++res;
	if (grid[i + 1][j] == 0)	++res;
	return res;
}
int islandPerimeter(vector<vector<int>>& grid) {
	int row = grid.size(), col = grid[0].size();
	for (int i = 0; i != row; ++i) {
		grid[i].insert(grid[i].begin(), 0);
		grid[i].push_back(0);
	}
	grid.insert(grid.begin(), vector<int>(col + 1, 0));
	grid.push_back(vector<int>(col + 1, 0));
	int res = 0;
	for (int i = 1; i <= row; ++i) {
		for (int j = 1; j <= col; ++j)
			if (grid[i][j])
				res += helpIslandPerimeter(grid, i, j);
	}
	return res;
}
int findSubstringInWraproundString(string p) {
	int n = p.size(), len = 0;
	vector<int> dp(26, 0);
	for (int i = 0; i != n; ++i) {
		if (i > 0 && (p[i] - p[i - 1] == 1 || p[i] - p[i - 1] == -25)) {
			++len;
		}
		else {
			len = 1;
		}
		dp[p[i] - 'a'] = max(dp[p[i] - 'a'], len);
	}
	int res = accumulate(dp.begin(), dp.end(), 0);
	return res;
}
int rand7() {
	return rand() % 7 + 1;
}
int rand10() {
	int a = rand7(), b = rand7();
	if (a > 4 && b < 4)  return rand10();
	else          return (a + b) % 10 + 1;
}
bool helpMakesquare(vector<int>& nums, vector<int>& sums, int pos, int target) {
	if (pos >= nums.size()) {
		return sums[0] == target && sums[1] == target && sums[2] == target && sums[3] == target;
	}
	//对于当前这个火柴，尝试拼入上下左右四个边
	for (int i = 0; i < 4; ++i) {
		if (sums[i] + nums[pos] > target) continue;
		sums[i] += nums[pos]; //把当前火柴从i个边中拿出来，好尝试下一条边
		if (helpMakesquare(nums, sums, pos + 1, target)) return true;  //如果这个火柴被成功使用，就开始尝试拼下一根火柴
		sums[i] -= nums[pos];  //用当前火柴拼第i个边
	}
	return false;
}
bool makesquare(vector<int>& nums) {
	if (nums.empty() || nums.size()<4) return false;
	int sum = accumulate(nums.begin(), nums.end(), 0);
	if (sum % 4 != 0) return false;
	vector<int> sums(4, 0);  //长度为4的数组sums来保存每个边的长度和
	sort(nums.rbegin(), nums.rend());
	return helpMakesquare(nums, sums, 0, sum / 4);
}
int findMaxForm(vector<string>& strs, int m, int n) {
	int len = strs.size(), zero = 0, one = 0;
	vector<vector<int>> flag(m + 1, vector<int>(n + 1, 0));
	for (int i = 0; i != len; ++i) {
		zero = one = 0;
		for (int j = 0; j != strs[i].size(); ++j)
			strs[i][j] == '0' ? ++zero : ++one;
		for (int k = m; k >= zero; --k)
			for (int l = n; l >= one; --l)
				flag[k][l] = max(flag[k][l], flag[k - zero][l - one] + 1);
	}
	return flag[m][n];
}
int findRadius(vector<int>& houses, vector<int>& heaters) {
	sort(heaters.begin(), heaters.end());
	int head = heaters.front() - 1, tail = houses.size() - heaters.back();
	int res = max(head, tail);
	for (int i = 1; i != houses.size(); ++i)
		res = max(res, (heaters[i] - heaters[i - 1]) / 2);
	return res;
}
int findComplement(int num) {
	int mask = 0, temp = num;
	while (temp) {
		temp >>= 1;
		mask <<= 1;
		mask += 1;
	}
	return num ^ 0xFFFFFFFF & mask;
}
int totalHammingDistance(vector<int>& nums) {
	int mask = 1, res = 0;
	for (int i = 1; i != 31; ++i) {
		int zeros = 0, ones = 0;
		for (int j = 0; j != nums.size(); ++j)
			mask & nums[j] ? ++ones : ++zeros;
		res += zeros * ones;
		mask <<= 1;
	}
	return res;
}
class Cir {
private:
	int PI = 3.1415926;
	double r;
	double x;
	double y;
public:
	Cir(double radius, double x_center, double y_center) :
		r(radius), x(x_center), y(y_center){}

	vector<double> randPoint() {
		double rad = rand() / (RAND_MAX / r);
		double ang = rand() / (RAND_MAX / PI);
		return { rad * sin(ang), rad * cos(ang) };
	}
};
void helpMedianSlidingWindow(vector<int>& nums, int loc, map<int, int, greater<int>>& small, map<int, int, less<int>>& big) {
	int ssize = 0, bsize = 0;
	for (auto s : small)
		ssize += s.second;
	for (auto b : big)
		bsize += b.second;
	if (ssize > bsize) {
		if (nums[loc] >= small.begin()->first)
			++big[nums[loc]];
		else {
			++big[small.begin()->first];
			if (--small.begin()->second == 0)
				small.erase(small.begin()->first);
			++small[nums[loc]];
		}
	}
	else {
		if (nums[loc] <= big.begin()->first)
			++small[nums[loc]];
		else {
			++small[big.begin()->first];
			if (--big.begin()->second == 0)
				big.erase(big.begin()->first);
			++big[nums[loc]];
		}
	}
}
double helpMidI2D(long long a, long long b) {
	return static_cast<double>(a) + static_cast<double>(b - a) / 2.0;
}
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
	vector<double> res;
	if (k == 1) {
		for (int temp : nums)
			res.push_back(temp);
		return res;
	}
	int len = nums.size();
	map<int, int, greater<int>> small;
	map<int, int, less<int>> big;
	++small[nums[0]];
	for (int i = 1; i != k && i != len; ++i)
		helpMedianSlidingWindow(nums, i, small, big);
	double mid = (k % 2 == 1 ? static_cast<double>(small.begin()->first) : helpMidI2D(small.begin()->first, big.begin()->first));
	res.push_back(mid);
	for (int i = k; i != len; ++i) {
		if (nums[i - k] <= mid) {
			if (--small[nums[i - k]] == 0)
				small.erase(nums[i - k]);
		}
		else {
			if (--big[nums[i - k]] == 0)
				big.erase(nums[i - k]);
		}
		helpMedianSlidingWindow(nums, i, small, big);
		mid = (k % 2 == 1 ? static_cast<double>(small.begin()->first) : helpMidI2D(small.begin()->first, big.begin()->first));
		res.push_back(mid);
	}
	return res;
}
string licenseKeyFormatting(string S, int K) {
	if (S.empty())	return "";
	while (S.back() == '-')
		S.pop_back();
	int len = S.size(), n = 0;
	for (int i = 0; i != len; ++i) {
		if (S[i] == '-')
			++n;
	}
	int head = ((len - n) % K != 0 ? (len - n) % K : K);
	int i = 0, loc = 0;
	string res;
	while (i != head) {
		if (S[loc] != '-') {
			res.push_back(toupper(S[loc]));
			++i;
		}
		++loc;
	}
	while (loc != len) {
		res.push_back('-');
		int num = 0;
		while (num != K) {
			if (S[loc] != '-') {
				res.push_back(toupper(S[loc]));
				++num;
			}
			++loc;
		}
	}
	return res;
}
int findMaxConsecutiveOnes(vector<int>& nums) {
	if (nums.empty())	return 0;
	int len = nums.size(), res = 0, temp = 0;
	for (int i = 0; i != len; ++i) {
		if (nums[i] == 1)
			++temp;
		else {
			if (temp > res)
				res = temp;
			temp = 0;
		}
	}
	return max(res, temp);
}
int Predicthelper(vector<int>& nums, int s, int e) {
	return s == e ? nums[e] : max(nums[e] - Predicthelper(nums, s, e - 1), nums[s] - Predicthelper(nums, s + 1, e));
}
bool PredictTheWinner(vector<int>& nums) {
	return Predicthelper(nums, 0, nums.size() - 1) >= 0;
}
void helpFindSubsequences(set<vector<int>>& res, const vector<int>& group, vector<int> temp, int loc) {
	for (int i = loc; i != group.size(); ++i) {
		temp.push_back(group[i]);
		if (temp.size() > 1)
			res.insert(temp);
		helpFindSubsequences(res, group, temp, i + 1);
		temp.pop_back();
	}
}
vector<vector<int>> findSubsequences(vector<int>& nums) {
	if (nums.empty())	return {};
	int len = nums.size();
	vector<bool> flag(len, true);
	set<vector<int>> groups, res;
	for (int loc = 0; loc != len; ++loc) {
		if (flag[loc]) {
			vector<int> temp;
			int max = nums[loc];
			for (int i = loc; i != len; ++i) {
				if (nums[i] >= max) {
					temp.push_back(nums[i]);
					max = nums[i];
					flag[i] = false;
				}
			}
			if (temp.size() > 1)
				groups.insert(temp);
		}
	}
	for (vector<int> group : groups)
		helpFindSubsequences(res, group, vector<int>(), 0);
	vector<vector<int>> res0;
	for (vector<int> r : res)
		res0.push_back(r);
	return res0;
}
vector<int> constructRectangle(int area) {
	int roof = sqrt(area);
	for (int i = roof; i != 0; --i) {
		if (!(area % i))
			return { i, area / i };
	}
}
int findPoisonedDuration(vector<int>& timeSeries, int duration) {
	if (timeSeries.empty())	return 0;
	int len = timeSeries.size(), times = 0, cur = timeSeries[0] + duration;
	for (int i = 1; i != len; ++i) {
		times += (cur < timeSeries[i]) ? duration : timeSeries[i] - timeSeries[i - 1];
		cur = timeSeries[i] + duration;
	}
	return times + duration;
}
vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
	if (findNums.empty())	return {};
	int len1 = findNums.size(), len2 = nums.size();
	stack<int> st;
	unordered_map<int, int> flag;
	st.push(nums[0]);
	for (int i = 1; i != len2; ++i) {
		while (!st.empty() && nums[i] > st.top()) {
			flag.insert({ st.top(), nums[i] });
			st.pop();
		}
		st.push(nums[i]);
	}
	while (!st.empty()) {
		flag.insert({ st.top(), -1 });
		st.pop();
	}
	vector<int> res;
	for (int i = 0; i != len1; ++i)
		res.push_back(flag[findNums[i]]);
	return res;
}
vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
	if (matrix.empty() || matrix[0].empty()) return {};
	int m = matrix.size(), n = matrix[0].size(), k = 0;
	vector<int> res(m * n);
	for (int i = 0; i != m + n - 1; ++i) {
		int low = max(0, i - n + 1), high = min(i, m - 1);
		if (i % 2 == 0) {
			for (int j = high; j >= low; --j)
				res[k++] = matrix[j][i - j];
		}
		else {
			for (int j = low; j <= high; ++j)
				res[k++] = matrix[j][i - j];
		}
	}
	return res;
}
vector<string> findWords(vector<string>& words) {
	unordered_map<char, int> flag;
	flag['q'] = 1;
	flag['w'] = 1; 
	flag['e'] = 1;
	flag['r'] = 1;
	flag['t'] = 1;
	flag['y'] = 1;
	flag['u'] = 1;
	flag['i'] = 1;
	flag['o'] = 1;
	flag['p'] = 1;
	flag['a'] = 2;
	flag['s'] = 2;
	flag['d'] = 2;
	flag['f'] = 2;
	flag['g'] = 2;
	flag['h'] = 2;
	flag['j'] = 2;
	flag['k'] = 2;
	flag['l'] = 2;
	flag['z'] = 3;
	flag['x'] = 3;
	flag['c'] = 3;
	flag['v'] = 3;
	flag['b'] = 3;
	flag['n'] = 3;
	flag['m'] = 3;
	int len = words.size();
	vector<string> res;
	for (int i = 0; i != len; ++i) {
		string temp = words[i];
		int tag = flag[tolower(temp[0])], n = 1;
		while (n != temp.size()) {
			if (flag[tolower(temp[n])] != tag)
				break;
			else
				++n;
		}
		if (n == temp.size())
			res.push_back(temp);
	}
	return res;
}
vector<int> findMode(TreeNode* root) {
	int max = 0, v = 0, num = 1;
	stack<TreeNode*> st;
	vector<int> res;
	TreeNode* temp = root;
	while (temp->left) {
		st.push(temp);
		temp = temp->left;
	}
	v = temp->val;
	temp = temp->right;
	while (!st.empty() || temp) {
		while (temp) {
			st.push(temp);
			temp = temp->left;
		}
		if (!st.empty()) {
			temp = st.top();
			if (temp->val == v)
				++num;
			else {
				if (num == max)
					res.push_back(v);
				else if (num > max) {
					res.clear();
					res.push_back(v);
					max = num;
				}
				num = 1;
				v = temp->val;
			}
		}
		temp = temp->right;
		st.pop();
	}
	if (num == max)
		res.push_back(v);
	else if (num > max) {
		res.clear();
		res.push_back(v);
		max = num;
	}
	return res;
}
class Solution00 {
public:
	vector<string> path;
	vector<vector<string>> result;

	vector<vector<string>> partition(string s) {
		solve(s, 0);
		return result;
	}
	// 检查是否为回文串
	bool isPalindrome(const string& s) {
		int begin = 0, end = s.length() - 1;
		while (begin < end) {
			if (s[begin] != s[end])
				return false;
			++begin;
			--end;
		}
		return true;
	}
	// 递归解决
	void solve(const string &s, int pos) {
		if (pos == s.length()) {
			result.push_back(path);
			return;
		}
		for (int i = pos; i < s.length(); ++i) {
			string prefix = s.substr(pos, i - pos + 1);	//以s[pos]字符开头的所有前缀
			if (!isPalindrome(prefix))                  //不是回文串就继续找
				continue;
			path.push_back(prefix);						//加入path
			solve(s, i + 1);							//从已经找到的回文串的下一个字符继续找
			path.pop_back();							//记得移除,path还要继续复用
		}
	}
};
bool wordBreak00(string s, vector<string>& wordDict) {
	if (s.empty())  return true;
	if (wordDict.empty())   return false;
	unordered_set<string> dict(wordDict.begin(), wordDict.end());
	int len = s.size();
	vector<bool> flag(len + 1, false);
	flag[0] = true;
	for (int i = 1; i != len + 1; ++i) {
		for (int j = 0; j != i; ++j) {
			if (flag[j] && dict.count(s.substr(j, i - j))) {
				flag[j] = true;
				break;
			}
		}
	}
	return flag.back();
}
int maxProduct00(vector<int>& nums) {
	if (nums.empty())   return 0;
	int minRes = nums[0], maxRes = nums[0];
	int len = nums.size(), res = nums[0];
	for (int i = 1; i != len; ++i) {
		minRes = min(nums[i], min(nums[i] * maxRes, nums[i] * minRes));
		maxRes = max(nums[i], max(nums[i] * maxRes, nums[i] * minRes));
		res = max(res, maxRes);
	}
	return res;
}
vector<int> intersect00(vector<int>& nums1, vector<int>& nums2) {
	if (nums1.empty() || nums2.empty()) return {};
	int len1 = nums1.size(), len2 = nums2.size();
	unordered_map<int, int> flag;
	vector<int> res;
	for (int temp : nums1)
		++flag[temp];
	for (int temp : nums2) {
		if (flag.count(temp) && flag.find(temp)->second > 0) {
			res.push_back(temp);
			--flag[temp];
		}
	}
	return res;
}
class MedianFinder000 {
public:
	/** initialize your data structure here. */
	MedianFinder000() : flag(false), hold(0) {

	}

	void addNum(int num) {
		qe.push(num);
		flag = flag ? false : true;
		if (!flag) {
			hold = qe.front();
			qe.pop();
		}
	}

	double findMedian() {
		return flag ? qe.front() : (qe.front() + hold) / 2.0;
	}
private:
	queue<int> qe;
	bool flag;
	int hold;
};
bool helpFindTrace(vector<vector<char>> sqr, string step, int i, int j, int loc) {
	if (loc == sqr.size())	return true;
	bool res = false;
	if (i >= 0 && i < sqr.size() && j >= 0 && j < sqr[0].size()) {
		if (sqr[i][j] == step[loc]) {
			res = helpFindTrace(sqr, step, i + 1, j, loc + 1) ||
				helpFindTrace(sqr, step, i, j + 1, loc + 1) ||
				helpFindTrace(sqr, step, i - 1, j, loc + 1) ||
				helpFindTrace(sqr, step, i, j - 1, loc + 1);
		}
	}
	return res;
}
bool findTrace(vector<vector<char>> sqr, string step) {
	if (step.empty())	return true;
	if (sqr.empty() || sqr[0].empty())	return false;
	int row = sqr.size(), col = sqr[0].size(), len = step.size();
	if (len > row * col)	return false;
	for (int i = 0; i != row; ++i) {
		for (int j = 0; j != col; ++j) {
			if (sqr[i][j] == step[0] && helpFindTrace(sqr, step, i, j, 0))
				return true;
		}
	}
	return false;
}
TreeNode* helpBST(vector<int>& nums, int left, int right) {
	if (left >= right)
		return nullptr;
	int mid = left + (right - left) / 2;
	TreeNode* head = new TreeNode(nums[mid]);
	head->left = helpBST(nums, left, mid);
	head->right = helpBST(nums, mid + 1, right);
	return head;
}
TreeNode* sortedArrayToBST0(vector<int>& nums) {
	if (nums.empty())   return nullptr;
	TreeNode* head = new TreeNode(0);
	return helpBST(nums, 0, nums.size());
}
vector<vector<int>> pathSum00(TreeNode* root, int sum) {
	if (!root)  return {};
	int tar = sum;
	vector<vector<int>> res;
	vector<int> path;
	stack<TreeNode*> st;
	TreeNode* temp = root, *hot = nullptr;
	while (temp) {
		st.push(temp);
		path.push_back(temp->val);
		tar -= temp->val;
		temp = temp->left;
	}
	while (!st.empty()) {
		temp = st.top();
		st.pop();
		if (!temp->right || temp->right == hot) {
			if (!temp->left && ! temp->right && tar == 0)
				res.push_back(path);
			tar += temp->val;
			path.pop_back();
			hot = temp;
		}
		else {
			st.push(temp);
			temp = temp->right;
			while (temp) {
				st.push(temp);
				path.push_back(temp->val);
				tar -= temp->val;
				temp = temp->left;
			}
		}
	}
	return res;
}
bool Pac(vector<vector<int>>& matrix, int x, int y) {
	if (x == 0 || y == 0)   return true;
	bool res = false;
	if (x > 0 && matrix[x - 1][y] <= matrix[x][y])
		res = res || Pac(matrix, x - 1, y);
	if (y > 0 && matrix[x][y - 1] <= matrix[x][y])
		res = res || Pac(matrix, x, y - 1);
	if (x < matrix.size() - 1 && matrix[x + 1][y] <= matrix[x][y])
		res = res || Pac(matrix, x + 1, y);
	if (y < matrix[0].size() - 1 && matrix[x][y + 1] <= matrix[x][y])
		res = res || Pac(matrix, x, y + 1);
	return res;
}
bool Alt(vector<vector<int>>& matrix, int x, int y) {
	if (x == matrix.size() - 1 || y == matrix[0].size() - 1)   return true;
	bool res = false;
	if (x > 0 && matrix[x - 1][y] <= matrix[x][y])
		res = res || Alt(matrix, x - 1, y);
	if (y > 0 && matrix[x][y - 1] <= matrix[x][y])
		res = res || Alt(matrix, x, y - 1);
	if (x < matrix.size() - 1 && matrix[x + 1][y] <= matrix[x][y])
		res = res || Alt(matrix, x + 1, y);
	if (y < matrix[0].size() - 1 && matrix[x][y + 1] <= matrix[x][y])
		res = res || Alt(matrix, x, y + 1);
	return res;
}
vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
	if (matrix.empty()) return {};
	int row = matrix.size(), col = matrix[0].size();
	if (!col)   return {};
	vector<pair<int, int>> res;
	for (int i = 0; i != row; ++i) {
		for (int j = 0; j != col; ++j) {
			if (Pac(matrix, i, j) && Alt(matrix, i, j))
				res.push_back({ i, j });
		}
	}
	return res;
}
class suduko {
	bool flag = false;
public:
	void helpSolve(vector<vector<char>>& board, int i, int j) {
		if (i == 9 || flag) {
			flag = true;
			return;
		}
		if (board[i][j] != '.')
			helpSolve(board, i + (j + 1) / 9, (j + 1) % 9);
		else {
			vector<bool> hot(10, true);
			for (int m = 0; m != 9; ++m) {
				if (board[i][m] != '.')
					hot[board[i][m] - '0'] = false;
				if (board[m][j] != '.')
					hot[board[m][j] - '0'] = false;
				if (board[i / 3 * 3 + m / 3][j / 3 * 3 + m % 3] != '.')
					hot[board[i / 3 * 3 + m / 3][j / 3 * 3 + m % 3] - '0'] = false;
			}
			for (int num = 1; num != 10; ++num) {
				if (hot[num]) {
					board[i][j] = num + '0';
					helpSolve(board, i + (j + 1) / 9, (j + 1) % 9);
					if (flag)   return;
					board[i][j] = '.';
				}
			}
		}
	}
	void solveSudoku(vector<vector<char>>& board) {
		helpSolve(board, 0, 0);
	}
};
int main()
{
	vector<vector<char>> aaa{
		{'5', '3', '.', '.', '7', '.', '.', '.', '.'}, 
		{'6', '.', '.', '1', '9', '5', '.', '.', '.'}, 
		{'.', '9', '8', '.', '.', '.', '.', '6', '.'}, 
		{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
		{'4', '.', '.', '8', '.', '3', '.', '.', '1'}, 
		{'7', '.', '.', '.', '2', '.', '.', '.', '6'}, 
		{'.', '6', '.', '.', '.', '.', '2', '8', '.'}, 
		{'.', '.', '.', '4', '1', '9', '.', '.', '5'}, 
		{'.', '.', '.', '.', '8', '.', '.', '7', '9'}
	};
	suduko sss;
	sss.solveSudoku(aaa);
	for (auto aa : aaa) {
		for (auto a : aa)
			cout << a << " ";
		cout << endl;
	}
	cout << endl;
}
