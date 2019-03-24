#include "testsfunctions.c"
#include "CUnit/Basic.h"

void test_create_node() // testando create_node
{
	node *new = (node *) malloc(sizeof(node));
	new->f = 10;								
	new->c = 'x';
	new->next = NULL;
	new->left = NULL;
	new->right = NULL;
	node *test = create_node('x', 10, NULL, NULL);

	CU_ASSERT(test != NULL);
	CU_ASSERT_EQUAL(new->f, test->f);
	CU_ASSERT_EQUAL(new->c, test->c);
	CU_ASSERT_PTR_EQUAL(new->next, test->next);
	CU_ASSERT_PTR_EQUAL(new->left, test->left);
	CU_ASSERT_PTR_EQUAL(new->right, test->right);
}

void test_add() // testando add
{
	node *new1 = create_node('x', 10, NULL, NULL);
	node *new2 = create_node('y', 6, NULL, NULL);

	node *test = add(NULL, 'x', 10, NULL, NULL); // lista vazia retorna um new..
	
	CU_ASSERT(test != NULL);
	CU_ASSERT_EQUAL(new1->f, test->f);
	CU_ASSERT_EQUAL(new1->c, test->c);
	CU_ASSERT_PTR_EQUAL(new1->next, test->next);
	CU_ASSERT_PTR_EQUAL(new1->left, test->left);
	CU_ASSERT_PTR_EQUAL(new1->right, test->right);

	test = add(test, 'y', 6, NULL, NULL); // lista com 1 elemento retorna head..
	
	CU_ASSERT(test != NULL);
	CU_ASSERT_EQUAL(new2->f, test->f);
	CU_ASSERT_EQUAL(new2->c, test->c);
	CU_ASSERT_PTR_EQUAL(new2->left, test->left);
	CU_ASSERT_PTR_EQUAL(new2->right, test->right);
}

void test_make_tree() // testando make_tree
{
	node *aux1, *aux2, *head, *tail;

	tail = create_node('y', 20, NULL, NULL); // criando 2 nos e fazendo uma lista com eles..
	head = create_node('x', 10, NULL, NULL);

	head->next = tail; // lista feita..

	aux1 = head;
	aux2 = tail;
	head = make_tree(head);

	CU_ASSERT(head != NULL);
	CU_ASSERT_EQUAL(head->c, '*');
	CU_ASSERT_EQUAL(head->f, 30);
	CU_ASSERT_EQUAL(head->left, aux1);
	CU_ASSERT_EQUAL(head->right, aux2);
}

void test_create_hash()
{
	hash_tree *new = create_hash();

	CU_ASSERT(new != NULL);
}

void test_create_stack() // estar como criars.. nome feio!
{
	stack *new = criars();
	CU_ASSERT(new != NULL);
}

void test_create_t_node()
{
	h_tree *new = (h_tree *) malloc(sizeof(h_tree));								
	new->c = 'x';
	new->left = NULL;
	new->right = NULL;
	h_tree *test = create_t_node('x', NULL, NULL);

	CU_ASSERT(test != NULL);
	CU_ASSERT_EQUAL(new->c, test->c);
	CU_ASSERT_PTR_EQUAL(new->left, test->left);
	CU_ASSERT_PTR_EQUAL(new->right, test->right);
}

int main()
{
	// Initialize the CUnit test registry
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

   // Sets the basic run mode, CU_BRM_VERBOSE will show maximum output of run details
   // Other choices are: CU_BRM_SILENT and CU_BRM_NORMAL

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_pSuite pSuite = NULL, pSuite2 = NULL;

	// Add a suite to the registry

	pSuite = CU_add_suite("TEST", 0, 0);

	// Always check if add was successful

	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Add the test to the suite

	if (NULL == CU_add_test(pSuite, "test - 1", test_create_node)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "test - 2", test_add)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "test - 3", test_make_tree)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "test - 4", test_create_hash)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "test - 5", test_create_stack)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite, "test - 6", test_create_t_node)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// Run the tests and show the run summary
	CU_basic_run_tests();
	return CU_get_error();
}
