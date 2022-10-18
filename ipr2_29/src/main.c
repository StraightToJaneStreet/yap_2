#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
  struct TreeNode* parent;
  int mark;
};

typedef struct TreeNode* PTreeNode;

PTreeNode TreeNode__new(int mark) {
  struct TreeNode* node = (PTreeNode) calloc(1, sizeof(struct TreeNode));
  node->mark = mark;
  node->parent = NULL;
  return node;
}

void TreeNode__set_parent(PTreeNode node, PTreeNode parent) {
  node->parent = parent;
}

int main() {
  int nodes_count, target_node;
  PTreeNode* nodes;

  FILE* fin = fopen("input.txt", "r");
  FILE* fout = fopen("output.txt", "w+");

  fscanf(fin, "%d\n", &nodes_count);

  nodes = (PTreeNode*) calloc(nodes_count, sizeof(PTreeNode));

  for (int i = 0; i < nodes_count; i++) {
    int p;

    nodes[i] = TreeNode__new(i);

    fscanf(fin, "%d", &p);
    if (p != -1) {
      TreeNode__set_parent(nodes[i], nodes[p]);
    }
  }

  fscanf(fin, "%d\n", &target_node);

  int path_length = 0;
  PTreeNode cursor = nodes[target_node];

  fprintf(fout, "Path:");


  while (cursor != NULL) {
    fprintf(fout, " %d", cursor->mark);
    cursor = cursor->parent;
    path_length++;
  }

  fprintf(fout, "\nLength: %d\n", path_length);

  return 0;
}