

bool check(string s, string t) {
	///if  t exist in s ;
	// returns false if exist..
	// i dont know why
	
	string str = t + "$" + s;
	int n = str.length();
	int Z[n];
	int L, R, k;
	L = R = 0;
	for (int i = 1; i < n; ++i) {
		if (i > R) {
			L = R = i;
			while (R < n && str[R - L] == str[R])
				R++;
			Z[i] = R - L;
			R--;
		}
		else {
			k = i - L;

			if (Z[k] < R - i + 1)
				Z[i] = Z[k];
			else {
				L = i;
				while (R < n && str[R - L] == str[R])
					R++;
				Z[i] = R - L;
				R--;
			}
		}
	}
	for (int i = 1; i < n; ++i) {
		if (Z[i] == t.length())
			return false;
	}
	return true;
}
