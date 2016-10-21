#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAXWIDTH = 512;
const int MAXHEIGHT = 512;


// reads a PPM file.
// Notice that: width and height are passed by reference!
void readImage(int image[MAXWIDTH][MAXHEIGHT], int &width, int &height) {
  char c;
  int x;
  ifstream instr;
  instr.open("city.pgm");

  // read the header P3
  instr >> c;  assert(c == 'P');
  instr >> c;  assert(c == '2');

  // skip the comments (if any)
  while ((instr>>ws).peek() == '#') { instr.ignore(4096, '\n'); }

  instr >> width;
  instr >> height;

  assert(width <= MAXWIDTH);
  assert(height <= MAXHEIGHT);
  int max;
  instr >> max;
  assert(max == 255);

  for (int row = 0; row < height; row++)
    for (int col = 0; col < width; col++)
      instr >> image[col][row];
  instr.close();
  return;
}

void writeImage(int image[MAXWIDTH][MAXHEIGHT], int width, int height) {
  ofstream ostr;
  ostr.open("outImage.pgm");
  if (ostr.fail()) {
    cout << "Unable to write file\n";
    exit(1);
  };

  // print the header
  ostr << "P2" << endl;
  // width, height
  ostr << width << ' ';
  ostr << height << endl;
  ostr << 255 << endl;

  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      assert(image[col][row] < 256);
      assert(image[col][row] >= 0);
      ostr << image[col][row] << ' ';
      // lines should be no longer than 70 characters
      if ((col+1)%16 == 0) ostr << endl;
    }
    ostr << endl;
  }
  ostr.close();
  return;
}

void highlight(int image[][MAXHEIGHT], int width, int height, int t1, int t2)
{
	// make all pixels below t1: 0   and make all pixels above t2: 255
	for (int w = 0; w < width; w++)
	{
		for (int h = 0; h < height; h++)
		{
			if (image[w][h] < t1)
			{
				image[w][h] = 0;
			}
			else if (image[w][h] > t2)
			{
				image[w][h] = 255;
			}
		}
	}

	return;
}

int main() {

  int inImage[MAXWIDTH][MAXHEIGHT];
  int outImage[MAXWIDTH][MAXHEIGHT];
  int imageWidth, imageHeight;
  int t1, t2;

  readImage(inImage, imageWidth, imageHeight);

 /* for(int i = 0; i<imageWidth; i++)
    for(int j = 0; j<imageHeight; j++) {
	cout << inImage[i][j] << " ";} */

  // filter
  for(int i = 0; i<imageWidth; i++)
    for(int j = 0; j<imageHeight; j++) {
      outImage[i][j] = inImage[i][j];
    };
  writeImage(outImage, imageWidth, imageHeight);

  //get threshholds from user
  cout << "Please enter your first threshhold (t1):" << endl;
  cin >> t1;
  cout << "Please enter the second threshhold (t2):" << endl;
  cin >> t2;
  //highlight the image
  highlight(image, width, height, t1, t2);
  //write the image
  writeImage(image, width, height);

  return 0;

}
