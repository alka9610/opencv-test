//#include <tesseract/baseapi.h>
//#include <leptonica/allheaders.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>


int findChar(char * array, int startIndex, char goalChar, int arrayLength, bool ascending)
{
  if(startIndex < arrayLength)
  {
    if(ascending)
    {
      for(int i = startIndex; i < arrayLength; i++)
      {
        char currentChar = (&array[0])[i];
        if(currentChar == goalChar)
        {
          return i;
        }
      }
    }
    else
    {
      for(int i = startIndex; i >= 0; i--)
      {
        char currentChar = (&array[0])[i];
        if(currentChar == goalChar)
        {
          return i;
        }
      }
    }
  }
  return -1;
}

int findLeft(char * array, int startIndex, int arrayLength)
{
  int newlineIndex = findChar(array, startIndex, '\n', arrayLength, false);
  int spaceIndex = findChar(array, startIndex, ' ', arrayLength, false);
  return std::max(newlineIndex, spaceIndex) + 1;
}

int findRight(char * array, int startIndex, int arrayLength)
{
  int newlineIndex = findChar(array, startIndex, '\n', arrayLength, true);
  int spaceIndex = findChar(array, startIndex, ' ', arrayLength, true);
  int min = std::min(newlineIndex, spaceIndex);
  if(min == -1)
  {
    return arrayLength - 1;
  }
  return min- 1;
}

std::string getString(char * array, int left, int right)
{
  std::stringstream sstr;
  for(int i = left; i <= right; i++)
  {
    sstr << (&array[0])[i];
  }
  return sstr.str();
}

std::stringstream getEmails(std::string filename)
{
  std::ifstream ifs (filename, std::ifstream::binary);

  ifs.seekg (0, ifs.end);
  int length = ifs.tellg();
  ifs.seekg (0, ifs.beg);

  char * buffer = new char [length];
  // read data as a block:
  ifs.read (buffer,length);

  ifs.close();

  int startIndex = 0;
  std::stringstream result;
  while(startIndex < length)
  {
    std::cout << "Current index: " << startIndex << std::endl;
    int snabelAIndex = findChar(buffer, startIndex, '@', length, true);
    int left = findLeft(buffer, snabelAIndex, length);
    int right = findRight(buffer, snabelAIndex, length);
    if(right < 0 || left < 0)
    {
      break;
    }
    std::string xd = getString(buffer, left, right);
    result << xd << "\n";
    startIndex = right;
  }
  return result;
}


int main()
{
    std::stringstream XD = getEmails("master-output.txt");
    std::ofstream myfile ("master-resultat.txt");
    if (myfile.is_open())
    {
      myfile << XD.str();
      myfile.close();
    }

    return 0;
    //
    // tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // // Initialize tesseract-ocr with English, without specifying tessdata path
    // if (api->Init(NULL, "eng")) {
    //     std::cerr << "Could not initialize tesseract." << std::endl;
    //     //exit(1);
    // }
    //
    // // Open input image with leptonica library
    // Pix *image = pixRead("/home/alexander/Downloads/imgs/img34.jpg");
    // api->SetImage(image);
    // // Get OCR result
    // outText = api->GetUTF8Text();
    // api->SetRectangle(2000, 0, 1300, 4680);
    // //std::cout << "Test xd: " << test << std::endl;
    // std::cout << "OCR output:\n" << outText << std::endl;
    //
    // // Destroy used object and release memory
    // api->End();
    // delete [] outText;
    // pixDestroy(&image);
    //
    // return 0;
}
