class SQRTDecomposition {
	private:
		int n, sz;
		vector<int> val;
		vector<int> blocks;
	public:
		inline void add(int v, int delta) {
			val[v] += delta;
			blocks[v / sz] += delta;
		}
		
		inline int sum(int l, int r) {	
			if (l < 0) {
				l = 0;
			}
			if (r >= n) {
				r = n;
			}
			r++;
			int res = 0;
			int lBlock = (l + sz - 1) / sz, rBlock = r / sz;
			for (int i = lBlock; i < rBlock; i++) {
				res += blocks[i];
			}
			int lBlockR = lBlock * sz, rBlockR = rBlock * sz;
			if (lBlockR >= rBlockR) {
				for (int i = l; i < r; i++) {
					res += val[i];
				}
			} else {
				for (int i = l; i < lBlockR; i++) {
					res += val[i];
				}
				for (int i = rBlockR; i < r; i++) {
					res += val[i];
				}
			}
			return res;
		}
		
		inline void clear() {
			val.assign(val.size(), 0);
			blocks.assign(blocks.size(), 0);
		}
		
		SQRTDecomposition(int n, int sz)
			: n(n), sz(sz), val(n, 0), blocks((n + sz - 1) / sz, 0) {
		}
};
