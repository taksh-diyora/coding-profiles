#include <bits/stdc++.h>
using namespace std;

struct Node {
    int g = 0;
    int count = 0;
};

class SGTree {
    vector<Node> seg;
public:
    SGTree(int n) {
        seg.resize(4 * n + 1);
    }

    Node mergeNodes(Node left, Node right) {
        if (left.g == 0) return right;
        if (right.g == 0) return left;

        Node res;
        res.g = gcd(left.g, right.g);

        if (left.g == res.g) {
            res.count += left.count;
        }

        if (right.g == res.g) {
            res.count += right.count;
        }

        return res;
    }

    void build(int ind, int low, int high, vector<int>& nums) {
        if (low == high) {
            seg[ind].g = nums[low];
            seg[ind].count = 1;
            return;
        }

        int mid = low + (high - low) / 2;
        build(2 * ind + 1, low, mid, nums);
        build(2 * ind + 2, mid + 1, high, nums);

        seg[ind] = mergeNodes(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    Node query(int ind, int low, int high, int l, int r) {
        if (l > high || r < low) {
            return {0, 0};
        } else if (l <= low && r >= high) {
            return seg[ind];
        }
        
        int mid = low + (high - low) / 2;
        Node left = query(2 * ind + 1, low, mid, l, r);
        Node right = query(2 * ind + 2, mid + 1, high, l, r);

        return mergeNodes(left, right);
    }
};

void solve() {
    int n;
    cin >> n;
    
    vector<int> ants(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ants[i];
    }

    SGTree S(n);
    
    S.build(0, 1, n, ants);

    int q;
    cin >> q;

    while (q--) {
        int l, r;
        cin >> l >> r;

        Node res = S.query(0, 1, n, l, r);

        int eaten = (r - l + 1) - res.count;
        cout << eaten << "\n";
    }
}

int main() {
    solve();
    return 0;
}