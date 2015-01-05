graph-t-IM-viral-marketing
==========================

An implementation of a Greedy algorithm for the t-Influence Maximization problem in Social Network Graphs

A modified version of the algorithm presented by S. Datta, A. Majumder, N. Shrivastava in “Viral Marketing for Multiple
Products”, ICDM 2010 for the t-Influence Maximization problem. The modified algorithm takes into account per-product probability of influence of one user on another.

The original algorithm is implemented in OriginalFairGreedy.cpp and the modified version in CustomFairGreedy.cpp. The CustomFairGreedy algorithm uses OpenMP for parallel processing and should be compiled with the fopenmp for best results.

How to run the algorithm(s):

1. First the data must be fetched from a Social Networking Website. Scripts are provided in the Data Collection folder to fetch the data from Facebook using the Facebook Graph API. The pipeline is:

    (a.) 1_facebook_get_friends.py - to fetch the like pages of all the friends of a person.

    (b.) 2_accumulate_likes.py - to get the set of all like pages (removing duplicates).

    (c.) 3_fetch_likepages_data.py - to fetch the content of all the like pages to be used for classification later.

    (d.) 4_facebook_get_adjlist.py - to create adjacency lists for all the nodes in the sub-network we are focusing on.


2. The fetched data must now be processed to convert the data into the format accepted by the algorithm. These are done for the data from step 1 using the following scripts/programs:

    (a.) 1_like_classifier.py - to classify each of the fetched like pages as belonging to one of the products (or none) mentioned in Products.txt (see the sample file provided) based on the overall term frequency of all the terms mentioned against the product.

    (b.) 2_user_likes_adjlists.py - to associate like pages with users i.e. to create adjacency lists between users and like pages.

    (c.) 3_calculate_jaccard_values.cpp - to compute the Jaccard coefficients between adjacent users for each of the products based on the classification previously done.

    (d.) 4_weighted_adjacency.cpp - to use the Jaccard values computed above to weigh the edges of the Social Network.


3. Adjust the Input Parameters (Name of the product, product ID, target number of seeds) and run the two algorithms by selecting the number of runs of the Oracle (more runs = more accuracy, refer to the paper for further details).

4. The adjacency list of the Social Network graph can be converted into GML format for visualization using tools like Gephi.
