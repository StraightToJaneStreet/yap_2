#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <string.h>

struct TreeNode {
  struct TreeNode* parent;
  int mark;
  int value;
};

typedef struct TreeNode* PTreeNode;

PTreeNode TreeNode__new(int mark, int value) {
  struct TreeNode* node = (PTreeNode) calloc(1, sizeof(struct TreeNode));

  node->mark = mark;
  node->value = value;
  node->parent = NULL;

  return node;
}

void TreeNode__set_parent(PTreeNode node, PTreeNode parent) {
  node->parent = parent;
}

int find_path_to_root(PTreeNode p, int *buffer) {
  int length = 0;
  PTreeNode cursor = p;
  while (p != NULL) {
    buffer[length] = p->mark;
    p = p->parent;
    length++;
  }
  return length;
}

int main() {
  int nodes_count, target_value;
  PTreeNode* nodes;

  FILE* fin = fopen("input.txt", "r");
  FILE* fout = fopen("output.txt", "w+");

  fscanf(fin, "%d", &nodes_count);

  nodes = (PTreeNode*) calloc(nodes_count, sizeof(PTreeNode));
  for (size_t i = 0; i < nodes_count; i++) {
    int value;
    fscanf(fin, "%d", &value);
    nodes[i] = TreeNode__new(i + 1, value);
  }

  for (int i = 0; i < nodes_count; i++) {
    int p;
    fscanf(fin, "%d", &p);
    if (p != 0) {
      TreeNode__set_parent(nodes[i], nodes[p - 1]);
    }
  }

  fprintf(fout, "Nodes:\n");

  for (size_t i = 0; i < nodes_count; i++) {
    char prettyParent[10];

    PTreeNode node = nodes[i];
    if (node->parent == NULL) {
      sprintf(prettyParent, "None");
    } else {
      sprintf(prettyParent, "%d", node->parent->mark);
    }

    fprintf(fout, "Index: %lld; Value: %d; Parent Index: %s\n", i + 1, node->value, prettyParent);
  }

  fscanf(fin, "%d\n", &target_value);

  int results_count = 0;
  int* results[20];
  int results_lengths[20];
  int results_source_marks[20];

  for (int i = 0; i < nodes_count; i++) {
    int path_length;
    int path[20];

    PTreeNode node = nodes[i];

    if (node->value == target_value) {
      path_length = find_path_to_root(node, path);

      results[results_count] = (int*) calloc(path_length, sizeof(int));
      memcpy(results[results_count], path, path_length * sizeof(int));

      results_lengths[results_count] = path_length;
      results_source_marks[results_count] = node->mark;

      results_count++;
    }
  }

  fprintf(fout, "Results count: %d\n", results_count);

  for (int i = 0; i < results_count; i++) {
    fprintf(fout, "Path from vertex %d -", results_source_marks[i]);

    for (int j = 0; j < results_lengths[i]; j++) {
      fprintf(fout, " %d", results[i][j]);
    }

    fprintf(fout, "\n");
  }

  return 0;
}