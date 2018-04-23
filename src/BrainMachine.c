#include <libB.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

/** \file main.c
 * entry point of the brain machine.
 */

static void vm_help() {
  printf(
      "Usage: brain [--help] [-d] [--vmdebug] [--gcdebug] [--gcfreq=FF] "
      "prog.bc\n");
  printf("   ==> run Brainf**k program with VM\n");
  printf("Options:\n");
  printf("   -h, --help    : print this help and exit\n");
  printf("   -d, --vmdebug : start the VM in debug mode\n");
  printf("   -v, --verbose : start the VM in verbose mode\n");
  printf(
      "   --vmfreq=FF   : VM frequency set to FF (In Miliseconds) Not "
      "Compatible with Step\n");
  printf(
      "   -s, --step    : start the VM step by step mode, Not Compatible with "
      "Frequency\n");
  printf("\n");
}

/** Analyse functions of command line options */
int parse_debug_vm(int index, char* argv[]) {
  if (strcmp(argv[index], "-d") == 0 || strcmp(argv[index], "--vmdebug") == 0) {
    return 1;
  } else {
    return 0;
  }
}

int parse_step(int index, char* argv[]) {
  if (strcmp(argv[index], "-s") == 0 || strcmp(argv[index], "--step") == 0) {
    return 1;
  } else {
    return 0;
  }
}

int parse_verbose(int index, char* argv[]) {
  if (strcmp(argv[index], "-v") == 0 || strcmp(argv[index], "--verbose") == 0) {
    return 1;
  } else {
    return 0;
  }
}

int parse_vm_freq(int index, char* argv[]) {
  char buf[11];
  if (strncmp(argv[index], "--vmfreq=", 9) != 0) {
    return 0;
  }

  strncpy(buf, &(argv[index][9]), 10);

  long val = strtol(buf, NULL, 10);
  if (val == 0 && errno == EINVAL) {
    fprintf(stderr, "Incorrect vm frequency: %s\n", buf);
    exit(EXIT_FAILURE);
  }

  if (val <= 0) {
    fprintf(stderr, "vm frequency should be positive, given: %d\n", (int)val);
    exit(EXIT_FAILURE);
  }

  return (int)val;
}

int main(int argc, char* argv[]) {
  char* filename = NULL;
  BrainVM* b = initVM();
  int i;

  printf("BrainMachine v1.0 \n");
  printf("---------------------\n");

  if (argc <= 1) {
    fprintf(stderr, "Error: missing arguments\n");
    vm_help();
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    vm_help();
    exit(EXIT_SUCCESS);
  }

  for (i = 1; i < argc; i++) {
    if (parse_debug_vm(i, argv)) {
      if (b->debug_vm) {
        fprintf(stderr, "option -d or --vmdebug set twice\n");
        exit(EXIT_FAILURE);
      } else {
        b->debug_vm = 1;
      }
    } else if (parse_verbose(i, argv)) {
      if (b->verbose) {
        fprintf(stderr, "option -v or --verbose set twice\n");
        exit(EXIT_FAILURE);
      } else {
        b->verbose = 1;
      }
    } else if (parse_step(i, argv)) {
      if (b->step) {
        fprintf(stderr, "option -s or --step set twice\n");
        exit(EXIT_FAILURE);
      } else {
        b->step = 1;
      }
    } else {
      int freq = parse_vm_freq(i, argv);
      if (freq == 0) {
        filename = argv[i];
        if (argc > i + 1) {
          fprintf(stderr, "too many arguments\n");
          exit(EXIT_FAILURE);
        }
        break;
      } else {
        b->vm_freq = freq;
      }
    }
  }
  if (b->debug_vm) {
    printf("starting VM in debug mode\n");
  }
  if (b->step) {
    printf("starting VM in step mode\n");
  }
  if (b->verbose) {
    printf("starting VM in verbose mode\n");
  }
  if (b->vm_freq > 0 && b->step == 1) {
    fprintf(stderr,
            "Step by step execution and set frequency not Compatible\n");
    exit(EXIT_FAILURE);
  }

  if (b->vm_freq > 0) {
    printf("VM frequency = %d\n", b->vm_freq);
  }

  printf("loading file: %s\n", filename);

  parse(filename, b);

  if (b->debug_vm) {
    printf("=== Loaded program:\n");
    printCode(b);
    printf("\n===================\n");
    printf("=== Data about program:\n");
    printData(b);
    printf("===================\n");
  }

  printf("-------------------\n");
  if (b->debug_vm) {
    printf("=== Begin execution ====\n");
  }

  int nb_inst = executeCode(b);

  if (b->debug_vm) {
    printf("=== Finish execution ====\n");
    printf("%d Instructions executed\n", nb_inst);
  }

  freeVM(b);

  printf("-------------------\n");
  printf("VM stopping\n");

  return EXIT_SUCCESS;
}