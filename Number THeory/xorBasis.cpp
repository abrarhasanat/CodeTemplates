int basis[d]; // basis[i] keeps the mask of the vector whose f value is i

int sz; // Current size of the basis

void insertVector(int mask) {
    for (int i = 0; i < logA; i++) {
        if ((mask & (1LL << i)) == 0) continue; // continue if i != f(mask)

        if (!basis[i]) { // If there is no basis vector with the i'th bit set, then insert this vector into the basis
            basis[i] = mask;
            ++sz;

            return;
        }

        mask ^= basis[i]; // Otherwise subtract the basis vector from this vector
    }
}

bool isInVectorSpace(int x) {
    for (int i = 0; i < logA; ++i) {
        if ((mask & (1LL << i)) == 0) continue;
        if (!basis[i]) return false;
        x ^= basis[i];
    }
    return true;
}



