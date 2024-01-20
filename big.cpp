#include <iostream>
#include <vector>
#include <string>

class big{
private:
    std::string st;
    std::vector<int> num;
    bool positive = true;
public:
    /*void isPositive(){

    }*/
    big(){}
    //ex: big a("12345");
    big(std::string s): st(s){
        for(int i = 0; i < st.length(); i++)
            num.push_back(st[i] - '0');
    }
    //ex: cin >> (big) a;
    friend std::istream& operator>>(std::istream& is, big& s){
        is >> s.st;
        int i;
        if(s.st[0] == '-'){
            i = 1;
            s.positive = 0;
        }
        else if(s.st[0] == '+'){
            i = 1;
            s.positive = 1;
        }
        else{
            i = 0;
            s.positive = 1;
        }
        for(; i < s.st.length(); i++){
            s.num.push_back(s.st[i] - '0');
        }
        return is;
    }
    //ex: cout << (big) a;
    friend std::ostream& operator<<(std::ostream& os, const big& s){
        if(!s.positive){
            os << '-';
        }
        for(int i = 0; i < s.num.size(); i++){
            os << s.num[i];
        }
        return os;
    }
    //ex: (big) a = (string) "12345";
    void operator=(std::string s){
        st = s;
        int i;
        if(st[0] == '-'){
            positive = 0;
            i = 1;
        }
        else{
            i = 0;
        }
        num.clear();
        for(; i < st.length(); i++)
            num.push_back(st[i] - '0');
    }
    //ex: (big) a = (int) 12345;
    void operator=(int n){
        *this = std::to_string(n);
    }
    //ex: (big) a = (big) b;
    void operator=(const big &s){
        this->num = s.num;
        this->positive = s.positive;
    }
    //ex: (big) a[(int) n];
    int operator[](int n){
        return num[n];
    }
    big operator-(const big& b){
        big res, tmp;
        tmp = *this;
        int t = this->num.size()-1, o = b.num.size()-1;
        for(int i = 0; i < this->num.size(); i++)
            res.num.push_back(0);
        while(0 <= t || 0 <= o){
            if((this->num[t] - b.num[o]) < 0 && t) this->num[t-1]--; this->num[t] += 10;
            res.num[t] = this->num[t] - b.num[o];
            t--; o--;
        }
        return res;
    }
    //ex: (big) a + (big) b;
    big operator+(const big& s){
        big res; 
        int t = this->num.size()-1, o = s.num.size()-1, r = t + o + 1;
        int t_val, o_val, carry, tmp;
        for(int i = 0; i < this->num.size() + s.num.size(); i++)
            res.num.push_back(0);
        while(0 <= t || 0 <= o){
            if(0 <= t) t_val = this->num[t]; else t_val = 0;
            if(0 <= o) o_val = s.num[o]; else o_val = 0;
            tmp = t_val + o_val;
            res.num[r] += tmp % 10;
            res.num[r-1] += tmp / 10;
            t--; o--; r--;
        }
        for(int i = res.num.size()-1; 0 <= i; i--){
            res.num[i-1] += res.num[i] / 10;
            res.num[i] = res.num[i] % 10;
        }
        while(res.num[0] == 0)
            res.num.erase(res.num.begin());
        return res;
    }
    //ex: (big) a + (int) n;
    big operator+(int n){
        big res(std::to_string(n));
        return *this + res;
    }
    //ex: (big) a = (big) b * (int) c;
    big operator*(const int s){
        big res("0");
        for(int i = 0; i < s; i++){
            res = res + *this;
        }
        return res;
    }
};
