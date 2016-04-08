#ifndef CORE_H
#define CORE_H

#define del_ptr(p)  { delete p; p = NULL; }
#define del_arr(p)  { delete [] p; p = NULL; }

#endif // CORE_H