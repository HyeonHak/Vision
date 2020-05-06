#include <cstdlib>
#include <iostream>

#define WIDTH 640
#define HEIGHT 320

using namespace std;

int view_info(int width, int height, int left, int top, int right, int bottom)
{
    cout<<"***Input ERROR***\n";
    cout<<"CURRENT INPUT VALUE \n";
    cout<<"left : "<<left<<"\ntop : "<<top<<"\nright : "<<right<<"\nbottom :"<<bottom;
    cout<<"\n\nInputable value\n"<<"width : 0 ~ "<<width - 1<<"\nheight : 0 ~ "<<height - 1<<"\n";
    return (-1);
}
int check_input(int width, int height, int left, int top, int right, int bottom)
{
    //left의 값이 right 보다 클 때 에러
    int check = 0;
    if (left > right || top > bottom)
        return view_info(WIDTH,HEIGHT, left, top, right, bottom);
    if (width <= right || height <= bottom)
        return view_info(WIDTH,HEIGHT, left, top, right, bottom);
    return (1);
}

void integral_image(unsigned char* image, int width, int height, unsigned int* ii_image) 
{
    ii_image[0] = image[0];
    for (int i=1; i<WIDTH;i++) ii_image[i] = image[i] + ii_image[i - 1];
    ii_image[WIDTH] = image[WIDTH] + ii_image[0];

    for (int i=WIDTH+1; i<WIDTH*HEIGHT; i++)
        ii_image[i] = image[i] + ii_image[i - 1] + ii_image[i - WIDTH] - ii_image[i - WIDTH - 1];
}

int integral_image_sum_value(unsigned int* ii_image, int width, int height, int left, int top, int right, int bottom) 
{
    int ret = 0;
    
    ret = ii_image[(bottom * WIDTH) + right];
    if (right - left - 1 >= 0) 
    {
        ret -= ii_image[bottom * WIDTH + left - 1];
        if (top - 1 >= 0)
            ret += ii_image[(top - 1) * WIDTH + left - 1];
    }
    if (top - 1 >= 0) ret -= ii_image[(top - 1) * WIDTH + right];

    return (ret);
}

int image_sum_value(unsigned char* image, int width, int height, int left, int top, int right, int bottom)
{
    int ret = 0;
    if (check_input(WIDTH,HEIGHT, left, top, right, bottom))
    {
        int cnt = 0;
        for (int i=top;i<=bottom;i++){
            for (int j=left;j<=right;j++)
                ret += image[(WIDTH * i) + j];
            cnt++;
        }
    }
    return (ret);
}

int main()
{
	unsigned char* image = new unsigned char[WIDTH*HEIGHT];
	unsigned int* ii_image = new unsigned int[WIDTH*HEIGHT];
	for(int i=0; i<WIDTH*HEIGHT; i++) image[i] = rand()%256;
	integral_image(image, WIDTH, HEIGHT, ii_image);
	int sum1 = integral_image_sum_value(ii_image, WIDTH, HEIGHT, 10, 20, 50, 100);
	int sum2 = image_sum_value(image, WIDTH, HEIGHT, 10, 20, 50, 100);
    if(sum1 != sum2) cout<<"error\n";
	delete[] image;
	delete[] ii_image;

}