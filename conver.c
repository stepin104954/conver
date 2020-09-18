#include <iostream.h>     // std::cout, std::cin, std::endl
#include <vector.h>       // std::vector
#include <algorithm.h>    // std::reverse

const std::vector<std::string> first_twenty_vocabular = {
        "zero ",
        "one ",
        "two ",
        "three ",
        "four ",
        "five ",
        "six ",
        "seven ",
        "eight ",
        "nine ",
        "ten ",
        "eleven ",
        "twelve ",
        "thirteen ",
        "fourteen ",
        "fifteen ",
        "sixteen ",
        "seventeen ",
        "eighteen ",
        "nineteen " };

const std::vector<std::string> magnitude_vocabular = {
        "hundred ",
        "thousand ",
        "million ",
        "billion "};

const std::vector<std::string> decine_vocabular = {
        "twenty ",
        "thirty ",
        "fourty ",
        "fifty ",
        "sixty ",
        "seventy ",
        "eighty ",
        "ninety "};

// HERE THE MAGIC HAPPENS.
std::string Stringer(std::vector<int> src);
        // Translate the number up to the hundreds, if the number is bigger it sends it to MagnitudeSplitte() for splitting it up.

std::string MagnitudeSplitter(std::vector<int> src);
        // Splits a number too big for Stringer to handle into smaller chunks (using VectorSplitter()) of max 3 digits, translate them with Stringer() and appends the right magnitude.

std::vector<int> VectorSplitter(std::vector<int> &V);
        // Splits the number by the hundreds.
        // Ex:  12004 is split into 12 and 004.
        //      1222333 is split into 1 and 222333.
        //      111222 is split into 111 and 222.
// ######################################################

// THESE FUNCTIONS ARE HELPER FUNCTIONS TO Stringer().
std::string units(std::vector<int> src);
        // Translate the singe digits numbers.

std::string decine(std::vector<int> src);
        // Transalte the double digits numbers.
        // ( Considered the structure of the vocabular vectors, i'm considering merging both units and decine into the same function.)

std::string hundreds(std::vector<int> src);
        // Transalte the triple digits numbers.
// #############################################################

// TOOLS.
void FlipVector(std::vector<int>& V) {
        std::reverse(V.begin(), V.end());
}

void PrintVector(std::vector<int> v) {
        int len = v.size();
        for (int i  = 0; i < len; ++i) { std::cout << v[i];}
        std::cout << std::endl;
}

std::vector<int> Splitter(int src_num) {
        // Convert the input number into a vector.
        std::vector<int> v_Digits;
        if (src_num == 0) {
                v_Digits.push_back(0);
                return v_Digits;
        }
        else {
                while(src_num >= 10) {
                        v_Digits.push_back(src_num%10);
                        src_num /= 10;
                }
                v_Digits.push_back(src_num);
                return v_Digits;
        }
}
// ###################################################

std::string units(std::vector<int> src) {
        std::string uni_str = first_twenty_vocabular[src[0]];
        return uni_str;
}

std::string decine(std::vector<int> src) {
        std::string dec_str = "";
        if (src[0] == 0) {
                if (src[1] == 0) { return dec_str; }
                else {
                        dec_str.append(first_twenty_vocabular[src[1]]);
                        return dec_str;
                }
        }
        else if (src[0] == 1) {
                dec_str.append(first_twenty_vocabular[10+src[1]]);
                return dec_str;
        }
        else {
                dec_str.append(decine_vocabular[src[0]-2]);
                if(src[1] == 0) { return dec_str; }
                else {
                        dec_str.append(first_twenty_vocabular[src[1]]);
                        return dec_str;
                }
        }
}

std::string hundreds(std::vector<int> src) {
        std::string hundred_string = "";

        if(src[0] == 0) {
                std::vector<int> dec_vec= {src[1],src[2]};
                std::string dec_str = decine(dec_vec);
                hundred_string.append(dec_str);
                return hundred_string;
        }
        else {
                hundred_string.append(first_twenty_vocabular[src[0]]);
                hundred_string.append("hundred ");
                std::vector<int> dec_vec= {src[1],src[2]};
                std::string dec_str = decine(dec_vec);
                hundred_string.append(dec_str);
                return hundred_string;
        }
}


std::string Stringer(std::vector<int> src) {
        std::string num_string = "";
        int len = src.size();
        if( src[0] < 0 ) {
                num_string.append("minus ");
                for (int i = 0; i < len; ++i) { src[i] = -i; }
        }

        if (len == 1) {
                std::string add = units(src);
                num_string.append(add);
        } else if (len == 2) {
                std::string add = decine(src);
                num_string.append(add);
        } else if (len == 3) {
                std::string add = hundreds(src);
                num_string.append(add);
        } else {
                return MagnitudeSplitter(src);
        }
        return num_string;
}

std::vector<int> VectorSplitter(std::vector<int> &V){
        std::vector<int> first_digits;
        int len = V.size();
        if (len%3 == 0) {
                for(int i = 0; i < 3; ++i) {
                        first_digits.push_back(V[0]);
                        FlipVector(V);
                        V.pop_back();
                        FlipVector(V);
                }

        } else {
                for( int i = 0; i < (len-(3*(len/3))); ++i) {
                        first_digits.push_back(V[0]);
                        FlipVector(V);
                        V.pop_back();
                        FlipVector(V);
                }
        }

        return first_digits;
}


std::string MagnitudeSplitter(std::vector<int> src) {
        int len = src.size();
        std::string tot_str = "";

        if (len == 3) {
                return Stringer(src);
        } else {
                std::vector<int> first_digits = VectorSplitter(src);
                int new_len = first_digits.size();
                std::string add = Stringer(first_digits);

                int sum_values = 0;    // To know if there are only zeroes.
                for ( int i = 0; i < new_len; ++i) {
                        sum_values += first_digits[i];
                }

                tot_str.append(add);
                if (sum_values) {
                        // Appends the right magnitude only if the relative chunk is significative ( with something in it).
                        tot_str.append(magnitude_vocabular[(len-1)/3]);
                }

                std::string return_str = Stringer(src);
                tot_str.append(return_str);
        }
        return tot_str;
}

int main() {
        std::cout << "insert your number: "; int x; std::cin >> x;
        std::vector<int> v_result = Splitter(x); // Face down, ass up.
        FlipVector(v_result);                    // Face up, ass down (poor boy)
        PrintVector(v_result);
        std::cout << Stringer(v_result) << std::endl;


}
