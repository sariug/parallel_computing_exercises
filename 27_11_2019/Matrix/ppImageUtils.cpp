#include "ppImageUtils.hpp"
using namespace std;


namespace imageProcessing
{
Matrix read_image(std::string filename)
{
    return Matrix( implementation::read_pgm_image(filename.c_str()));
}
void write_image(std::string filename, const Matrix & img)
{
    implementation::write_pgm_image(filename.c_str(),img);           /*Writing the PGM in Binary (P5) format*/
}
}


/* Implementations of reader and writer*/
namespace implementation
{
    
    Matrix read_pgm_image(const char* filnam) /*reads PGM images*/
    {
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
        int C=0, R=0;
        for (int i = 0; i < 4; i++)
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
                    implementation::bits = N1;
                }
            }
            else
            {
                std::cout << "\n Overread into bits!! Going back to bit line!!! \n";
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
            getline(newp, newlin);
        cout<<"The image imported is : "<<filnam<<std::endl;
        cout << "\tFiletype : "<<filemod<<std::endl;
        cout << "\t"<< "Height : "<<R<<std::endl;
        cout << "\t"<< "Width : "<<C<<std::endl;
        cout << "\t"<< "Maximum Value : "<<bits<<std::endl;

        Matrix m_img(R,C);

        long cnt = 0;

        for (auto k = 0; k < R; k++)
        {
            for (auto l = 0; l < C; l++)
            {

                if (newp.eof() == 1)
                    break;

                int val = 0;
                int p = 7;
                char c11;
                newp.get(c11);

                while (p >= 0)
                {

                    val += (((c11 >> p) & 1)) * pow(2, p);
                    p--;
                }

                m_img(k,l) = val;

                cnt++;
            }
        }

        newp.close();

        return m_img;
    }
    void write_pgm_image(const char* filnam, const Matrix &img) /*writes PGM images*/
    {
        int R, C;
        C = img.numberOfCols();
        R = img.numberOfRows();
        
        ofstream off;

        off.open(filnam, ios::out);
        off << implementation::filemod << "\n"
            << "# Filename :: CV 2017 " << filnam << "\n"
        << C << " " << R << "\n"
        << implementation::bits << "\n";
        cout<<"The image exported is : "<<filnam<<std::endl;
        cout << "\tFiletype : "<<filemod<<std::endl;
        cout << "\t"<< "Height : "<<R<<std::endl;
        cout << "\t"<< "Width : "<<C<<std::endl;
        cout << "\t"<< "Maximum Value : "<<bits<<std::endl;
        off.close();

        ofstream newof;

        newof.open(filnam,ios::out | ios::binary | ios::app);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)      
                newof.put(static_cast<int>(img(i,j)));
        newof.close();
    }
} // namespace implementation