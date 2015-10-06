# Lib distance version JAVA

Translation from C++ to JAVA of the library "distance"

## Use

The constructor called uses the path of the model word2vec (in binary mode):
```java
Lib_distance test = new Lib_distance(fileName);
```

You can get the cosine similarity between two words:
```java
test.getSimilarity(w1,w2);
```

Or the cosine distance between two words (the reverse of the cosine similarity):
```java
test.getSimilarity(w1,w2);
```


