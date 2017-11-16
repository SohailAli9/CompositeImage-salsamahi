#include "bitmap.h"
#include<iostream>
#include <string>
#include <vector>
void joinPictures(int, int arr[][2], std::vector <std::string>);
void CheakFile(std::vector <std::string>);
int main()
{
        std::vector <std::string> files;
        std::string userInput;
        int no_of_files = 1;
        std::cout << "Please enter name of file in bitmap format :  ";
        std::cout << "Maximum image allow is 10, Hit DONE after input name files\n";
        do
        {
                std::cout << "Please enter file name " << no_of_files << " (in .bmp extension) : ";
                std::getline(std::cin, userInput);//takign input from user
                if (userInput != "DONE")
                {
                        files.push_back(userInput);
                        no_of_files++;
                }//end if
        } while (userInput != "DONE" && no_of_files <10);//end do while
        std::cout << std::endl << std::endl << std::endl;
        CheakFile(files);
        system("pause");
        return 0;
}//end main/Driver func
void CheakFile(std::vector <std::string> vect){
        std::vector <std::string> temp;
        bool flag;
        int arr[10][2];
        int numOfFiles, R, C, a = 0;
        int NoOfValidFiles = 1;
        numOfFiles = vect.size();
        for (int i = 0; i<numOfFiles; i++){
                std::vector <std::vector <Pixel> > bitmap;
                Bitmap input_Image;
                C = R = 0;
                input_Image.open(vect[i]);
                if (input_Image.isImage()){
                        bitmap = input_Image.toPixelMatrix();
                        R = bitmap.size();
                        C = bitmap[0].size();
                        arr[a][0] = R;
                        arr[a][1] = C;
                        temp.push_back(vect[i]);
                        a++;
                }//end if
        }//end for loop
        if (a==1 || a<2){ // if less than 2 images
                std::cout << "Sorry, Can't create composite image cannot be formed\n";
                exit(0);
        }//end if
        if (a >= 2){ //true condition
                for (int x = 0; x<a; x++)
                        if (arr[0][0] == arr[x + 1][0] && arr[0][1] == arr[x + 1][1])
                                NoOfValidFiles++;
        }//end if
        joinPictures(NoOfValidFiles, arr, temp);
        std::cout << "Composite Image created successfully\n";
}//end cheakFiles function
void joinPictures(int no_of_files, int arr[][2], std::vector <std::string> vect){
        Bitmap *input_Image;
        Pixel *rgb; 
        input_Image = new Bitmap[no_of_files];
        rgb = new Pixel[no_of_files];
        std::vector < std::vector < std::vector<Pixel> > > bitmaps;
        Pixel pxl, average;
        int n = 0, k = 0, R = arr[n][0], C = arr[n][1], count = 1;
        while (count <= no_of_files){
                std::cout << "Image " << count << " of " << no_of_files << " Done :) \n";
                count++;
        }//end while loop
        for (n = 0; n<no_of_files; n++){
                input_Image[n].open(vect[n]);
                bitmaps.push_back(input_Image[n].toPixelMatrix());
        }//end for loop
        for (int x = 0; x<R; x++)
        {
                for (int y = 0; y<C; y++)
                {
                        pxl.red = 0;
                        pxl.green = 0;
                        pxl.blue = 0;
                        average.red = 0;
                        average.green = 0;
                        average.blue = 0;
                        for (k = 0; k<no_of_files; k++)
                                rgb[k] = bitmaps[k][x][y];
                        for (k = 0; k<no_of_files; k++)
                                pxl.red += rgb[k].red;
                        for (k = 0; k<no_of_files; k++)
                                pxl.green += rgb[k].green;
                        for (k = 0; k<no_of_files; k++)
                                pxl.blue += rgb[k].blue;
                        average.red = pxl.red / no_of_files;
                        average.green = pxl.blue / no_of_files;
                        average.blue = pxl.blue / no_of_files;
                        bitmaps[k - 1][x][y] = average;
                }//end inner for loop
        }//end outer for loop
        input_Image[n - 1].fromPixelMatrix(bitmaps[n - 1]);
        input_Image[n - 1].save("composite-SohailAli9.bmp");
}//end joinPictures
