#include <vcl_iostream.h>
#include <vcl_fstream.h>
#include <vcl_utility.h>

#include <vsl/vsl_test.h>
#include <vsl/vsl_binary_io.h>
#include <vsl/vsl_deque_io.h>

void test_deque_io()
{
  vcl_cout << "****************************" << vcl_endl;
  vcl_cout << "Testing vcl_deque binary io" << vcl_endl;
  vcl_cout << "****************************" << vcl_endl;

  int n = 10;
  vcl_deque<int> d_int_out;
  for (int i=0;i<n;++i)
    d_int_out.push_back(i);


  vsl_b_ofstream bfs_out("vsl_deque_io_test.bvl.tmp");
  TEST ("Created vsl_deque_io_test.bvl.tmp for writing", (!bfs_out), false);
  vsl_b_write(bfs_out, d_int_out);
  bfs_out.close();

  vcl_deque<int> d_int_in;

  vsl_b_ifstream bfs_in("vsl_deque_io_test.bvl.tmp");
  TEST ("Opened vsl_deque_io_test.bvl.tmp for reading", (!bfs_in), false);
  vsl_b_read(bfs_in, d_int_in);
  bfs_in.close();

  // kym - double equals not defined for deque??
  //TEST ("vcl_deque<int> out == vcl_deque<int> in",
  //    d_int_out == d_int_in, true);

  bool test_result = true;
  if (d_int_out.size() != d_int_in.size())
    test_result=false;
  else
  {
    for (int i=0;  i< d_int_out.size(); i++)
    {
      if (d_int_out[i] != d_int_in[i])
        test_result=false;
    }
  }
  TEST ("vcl_deque<int> out == vcl_deque<int> in", test_result, true);

  vsl_print_summary(vcl_cout, d_int_in);
  vcl_cout << vcl_endl;
}

TESTMAIN(test_deque_io);
