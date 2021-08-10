#include <iostream>
#include <vector>

const unsigned int THE_ONE = 1;

void mark(unsigned int n, std::vector<bool> &m, unsigned int sum, unsigned int mx) {
    if ((sum>=(THE_ONE<<n))&&(sum<=(THE_ONE<<(n+THE_ONE)))) {
        m[sum - (THE_ONE<<n)]=false;
    }
    if ((mx>=(THE_ONE<<n))&&(mx<=(THE_ONE<<(n+THE_ONE)))) {
        m[mx - (THE_ONE<<n)]=false;
    }

    if (sum<=(THE_ONE<<n))
    for (unsigned int i = THE_ONE; i<n+THE_ONE; i++) {
        mark(n,m,(sum^(mx<<i)),(mx<<i));
        if ((mx<<i)>=(THE_ONE<<31)) { break;}
    }
 }


int main()
 {
    unsigned int n;
    std::cin>>n;
    std::vector<bool> m((THE_ONE<<n),true);
    for (unsigned int i=2; i<(THE_ONE<<(n/2+THE_ONE)); i++) //n/2+THE_ONE??
        mark(n,m,i,i);
    n=0;
    for (unsigned int i=0; i<m.size(); i++)
        if (m[i]) n++;
    std::cout<<n<<std::endl;
 }
