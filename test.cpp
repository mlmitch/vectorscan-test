#include "hs.h"

#include <string>
#include <iostream>
#include <cassert>

using namespace std;

int main() {

  std::string pattern = u8"星{2}";
  hs_compile_error_t *error = nullptr;
  hs_database_t *db         = nullptr;
  int flags = HS_FLAG_UTF8 | HS_FLAG_SINGLEMATCH;

  hs_error_t ret = hs_compile(pattern.c_str(), flags, HS_MODE_BLOCK,
                              nullptr,&db,&error);
  if (ret != HS_SUCCESS) {
      std::cout << "hs_compile error msg: " << error->message << ". expression: " << error->expression << std::endl;
      hs_free_compile_error(error);
      error = nullptr;
  }
  assert(ret == HS_SUCCESS);

  hs_scratch_t *scratch = nullptr;
  ret = hs_alloc_scratch(db, &scratch);
  assert(ret == HS_SUCCESS);

  std::string scanText = u8"星星点灯";
  static int matchCount = 0;
  ret = hs_scan(db, scanText.c_str(), scanText.size(), 0, scratch,
                [](unsigned int id, unsigned long long from,
                   unsigned long long to, unsigned int flags,
                   void *context) -> int {
        //printMatchedInfo(id, from, to, flags, context);
        matchCount++;
        return 0;
      },
      nullptr);

  assert(ret == HS_SUCCESS);
  std::cout << "matchCount = " << matchCount << std::endl;
  assert(matchCount == 1);

  // cleanup
  hs_free_database(db);
  hs_free_scratch(scratch);
  matchCount = 0;
}
