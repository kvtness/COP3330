/*
    fbitvect.cpp
    01/05/09
    10/03/13 upgraded to batch mode option
    01/29/15 minor typos corrected
    Chris Lacher

    functionalty test of BitVector

    INTERACTIVE VERSION - command echo commented out

    Copyright 2009 - 2015, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bitvect.h>

// in lieu of a makefile (for command line creation of executable)
// #include <bitvect.cpp>

void DisplayMenu (unsigned int size);
void CopyTest    (fsu::BitVector bv);
void AssignTest  (fsu::BitVector * ptr);

// typedef alt::BitVector BitVector;
typedef fsu::BitVector BitVector;

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << " ** command line arguments:\n"
	      << "    1: number of bits requested [required]\n"
	      << "    2: \"batch\" [optional - for processing a file of commands]\n";
    return EXIT_FAILURE;
  }
  size_t size = atoi(argv[1]), index;

  std::ifstream ifs;
  std::istream* isptr = &std::cin;
  bool BATCH = 0;  

  if (argc > 2)
  {
    ifs.open(argv[2]);
    if (ifs.fail())
    {
      std::cout << " ** unable to read file \"" << argv[2] << "\"\n"
                << "    try again\n";
      return EXIT_FAILURE;
    }
    isptr = &ifs;
    BATCH = 1;
  }

  char selection;
  std::cout << "Welcome to fbitvect\n";
  BitVector * bvptr = new BitVector (size);
  DisplayMenu(size);
  do
  {
    std::cout << "  Enter [op][index] (\'M\' for menu, \'Q\' to quit): ";
    *isptr >> selection;
    if (BATCH)  std::cout << selection; // echo input
    switch(selection)
    {
      case '=':
	if (BATCH)  std::cout << '\n'; // echo input
	CopyTest(*bvptr);
	AssignTest(bvptr);
	break;
      case 'S':
	if (BATCH)  std::cout << '\n'; // echo input
        bvptr->Set();
        break;
      case 'U':
	if (BATCH)  std::cout << '\n'; // echo input
        bvptr->Unset();
        break;
      case 'F':
	if (BATCH)  std::cout << '\n'; // echo input
        bvptr->Flip();
        break;
      case 's':
        *isptr >> index;
	if (BATCH)  std::cout << index << '\n'; // echo input
        bvptr->Set(index);
        break;
      case 'u':
        *isptr >> index;
	if (BATCH)  std::cout << index << '\n'; // echo input
        bvptr->Unset(index);
        break;
      case 'f':
        *isptr >> index;
	if (BATCH)  std::cout << index << '\n'; // echo input
        bvptr->Flip(index);
        break;
      case 't': case 'T':
        *isptr >> index;
	if (BATCH)  std::cout << index << '\n'; // echo input
        std::cout << "  v[" << index << "] == ";
        if (bvptr->Test(index))
          std::cout << "1\n";
        else
          std::cout << "0\n";
        break;
      case 'e': case 'E':
        *isptr >> index;
	if (BATCH)  std::cout << index << '\n'; // echo input
        std::cout << " v.Expand(" << index << ")\n";
        bvptr->Expand(index);
        break;
      case 'd': case 'D':
	if (BATCH)  std::cout << '\n'; // echo input
	std::cout << " v.Size(): " << bvptr -> Size() << " ; v.Dump(std::cout):\n";
	bvptr->Dump(std::cout);
        break;
      case 'o': case 'O':
	if (BATCH)  std::cout << '\n'; // echo input
	std::cout << " std::cout << v: " << *bvptr << '\n';
        break;
      case 'm': case 'M':
	if (BATCH)  std::cout << '\n'; // echo input
        DisplayMenu(size);
        break;
      case 'x': case 'X':
	if (BATCH)
        {
          std::cout << '\n'; // echo input
          isptr = &std::cin;
          ifs.close();
          BATCH = 0;
          std::cout << " ** switched to interactive mode\n";
        }
        else
        {
          std::cout << " ** already in interactive mode\n";
        }
        break;
      case 'q': case 'Q': 
	if (BATCH)  std::cout << '\n'; // echo input
	selection = 'Q';
        if (BATCH)
          ifs.close();
        break;
      default:
	if (BATCH)  std::cout << '\n'; // echo input
        std::cout << "  command not found\n";
    }
  }
  while (selection != 'Q');
  delete bvptr;
  std::cout << "Thank you for testing BitVector\n";
  return 0;
}

void DisplayMenu(unsigned int size)
{
   std::cout << "     BitVector (" << size << ") v;\n"   
	     << "     operation                                entry\n"
	     << "     ---------                                -----\n"
	     << "     v.Set      ()  ............................  S\n"
	     << "     v.Set      (index)  .......................  s\n"
	     << "     v.Unset    ()  ............................  U\n"
	     << "     v.Unset    (index)  .......................  u\n"
	     << "     v.Flip     ()  ............................  F\n"
	     << "     v.Flip     (index)  .......................  f\n"
	     << "     v.Test     (index)  .......................  t\n"
	     << "     v.Expand   (newsize)  .....................  e\n"
	     << "     v.Dump     (std::cout)  ...................  d\n"
	     << "     std::cout << v  ...........................  o\n"
	     << "     copy, assign tests  .......................  =\n"
	     << "     display this Menu  ........................  m\n"
	     << "     switch to interactive mode  ...............  x\n"
	     << "     Quit program  .............................  q\n";
}


void CopyTest(fsu::BitVector bv)
{
  std::cout << "CopyTest:\n";
  std::cout << " Copied object   size: " << bv.Size() << '\n'
            << "                 Dump:\n";
  bv.Dump(std::cout);
  std::cout << '\n';
}

void AssignTest(fsu::BitVector * ptr)
{
  fsu::BitVector bv(0);
  bv  = *ptr;
  std::cout << "AssignTest:\n"
            << " Original object size: " << ptr->Size() << '\n'
            << "                 Dump:\n";
  ptr->Dump(std::cout);
  std::cout << '\n';
  std::cout << " Assignee object size: " << bv.Size() << '\n'
            << "                 Dump:\n";
  bv.Dump(std::cout);
  std::cout << '\n';
}

