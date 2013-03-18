#include <iostream>
#include <sstream>
#include <string>
#include <mpi.h>

using namespace std;

const int MAXLEN = 100;

int main(int argc, char* argv[]) {
  string greeting;
  ostringstream sout(greeting);
  int  comm_sz;  /* Number of processes */
  int  my_rank;  /* My process rank     */
  char buf[MAXLEN];

  MPI::Init(argc, argv);
  comm_sz=MPI::COMM_WORLD.Get_size();
  my_rank=MPI::COMM_WORLD.Get_rank();

  if (my_rank != 0) {
    sout<<"Greetings from process "<<my_rank<<" of "<<comm_sz<<"!";
    MPI::COMM_WORLD.Send(greeting.c_str(), greeting.size(), MPI_CHAR, 0, 0);
  } else {
    cout<<"Greetings from process "<<my_rank<<" of "<<comm_sz<<"!"<<endl;
    for (int q=1; q<comm_sz; q++) {
      MPI::COMM_WORLD.Recv(buf, MAXLEN, MPI_CHAR, q, 0);
      cout<<greeting<<endl;
    }
  }

  MPI::Finalize();
  return 0;
}
