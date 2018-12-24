#ifndef OUTPUTSTATISTIC_HPP
#define OUTPUTSTATISTIC_HPP

//fname is the full diraction of records\\[filename].amagoodR
void outputSort(char *fName);

//return nullptr(0) if memory shortage
int *operateSearchAndBuildArray(FILE *input,FILE *output,int wantX,int wantY,int &size);

#endif // OUTPUTSTATISTIC_HPP
