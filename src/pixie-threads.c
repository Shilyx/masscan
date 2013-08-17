#include "pixie-threads.h"

#if defined(WIN32)
#include <Windows.h>
#include <process.h>
#endif
#if defined(__linux__)
#include <unistd.h>
#include <pthread.h>
#endif

#ifndef UNUSEDPARM
#define UNUSEDPARM(x) x
#endif

/****************************************************************************
 ****************************************************************************/
size_t
pixie_begin_thread(void (*worker_thread)(void*), unsigned flags, void *worker_data)
{
#if defined(WIN32) && defined(_MT)
	UNUSEDPARM(flags);
	return _beginthread(worker_thread, 0, worker_data);
#elif defined(__GNUC__)
	typedef void *(*PTHREADFUNC)(void*);
	pthread_t thread_id;
	return pthread_create(&thread_id, NULL, (PTHREADFUNC)worker_thread, worker_data);
#else
#error pixie_begin_thread undefined
#endif
}