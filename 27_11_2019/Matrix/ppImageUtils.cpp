#include "ppImageUtils.hpp"
using namespace std;


/*PGM READ WRITE*/

vector<vector<int>> read_pgm_image(const char* filnam, char filemod[], char comment[], int &R, int &C, int &bits) /*reads PGM images*/
{
    std::cout<<filnam<<std::endl;
    vector<vector<int>> img;
    ifstream ifs;
    ifstream iftest;
    string newlin;
    iftest.open(filnam, ios::in);
    int header_size = 3;

    for (int i = 0; i < 4; i++)
    {

        getline(iftest, newlin);

        if (newlin.data()[0] == '#')
        {
            header_size = 4;
            break;
        }
    }

    iftest.close();

    ifs.open(filnam, ios::in);
    bool h = 0;
    int i = 0;

    for (int i = 0; i < header_size; i++)
    {
        streampos old = ifs.tellg();
        getline(ifs, newlin);

        int N1;
        stringstream t(newlin);
        t >> N1;

        if (strcmp(newlin.data(), "P2") == 0 | strcmp(newlin.data(), "P5") == 0)
        {
            strcpy(filemod, newlin.data());
        }
        else if (newlin.data()[0] == '#')
        {
            strcpy(comment, newlin.data());
        }
        else if (t)
        {

            int NN;
            t >> NN;
            if (t)
            {
                C = N1;
                R = NN;
            }
            else
            {
                bits = N1;
            }
        }
        else
        {
            cout << "\n Overread into bits!! Going back to bit line!!! \n";
            ifs.seekg(old);
            break;
        }
    }

    ifs.close();

    ifstream newp;
    newp.open(filnam, ios::in | ios::binary);

    char tt;
    newp >> tt;

    for (int i = 0; i < header_size; i++)
    {
        getline(newp, newlin);
    }
    cout << filemod << " : Filetype <-  \n";
    cout << comment << " : Comment <-  \n";
    cout << R << " : R - Height <-  \n";
    cout << C << " : C - Width <-  \n";
    cout << bits << " : Maximum Value <-  \n";

    vector<int> zvc(C);

    fill(zvc.begin(), zvc.end(), 0);

    for (int i = 0; i < R; i++)
    {
        img.push_back(zvc);
    }

    // for(int i = 0; i < R; i++)
    // {
    //
    //     for(int j = 0; i < C; j++)
    // {
    //
    //
    //     cout << img[i][j] << "   ";
    // }
    // }

    int k = 0, l = 0;
    long cnt = 0;

    for (k = 0; k < R; k++)
    {
        for (l = 0; l < C; l++)
        {

            if (newp.eof() == 1)
            {
                break;
            }

            int val = 0;
            int p = 7;
            char c11;
            newp.get(c11);

            while (p >= 0)
            {

                val += (((c11 >> p) & 1)) * pow(2, p);
                p--;
            }

            img[k][l] = val;

            cnt++;
        }
    }

    newp.close();

    return img;
}
#include <iostream>
void write_pgm_image(char filnam[], char filtype[], const vector<vector<double>> &img, int vals[]) /*writes PGM images*/
{
    int R, C, bits;
    C = img[0].size();
    R = img.size();
    bits = vals[2];

    ofstream off;

    off.open(filnam, ios::out);
    // off << filtype << "\n"
    //     << "# Filename :: CV 2017 " << filnam << "\n"
    //     << C << " " << R << "\n"
    //     << bits << "\n";
    off << "P5" << "\n"
        << "# Filename :: CV 2017 " << filnam << "\n"
        << C << " " << R << "\n"
        << 255 << "\n";

    off.close();

    ofstream newof;

    newof.open(filnam,ios::out | ios::binary | ios::app);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)      
            newof.put(static_cast<int>(img[i][j]));
        


    newof.close();
}

namespace imageProcessing
{
Matrix read_image(std::string filename)
{
    //char filnam[], char filemod[], char comment[], int &R, int &C, int &bits) /*reads PGM images*/

    char filt[1000];
    char comment[1000] = " ";
    int R, C, bits;
    int vals1[3];
    
    return Matrix( read_pgm_image(filename.c_str(), filt, comment, R, C, bits));
}
void write_image(std::string filename, const Matrix & img)
{
    int a[3]={1,2,3};
  write_pgm_image("result.pgm","a",img.m_matrix,a);           /*Writing the PGM in Binary (P5) format*/

}
}