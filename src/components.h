#include "flecs.h"


// Each Wikipedia link imported should generate an entity with two components
// One is a shared WikipediaLink
// The other is a page-specific empty struct, considered a Frame
// https://courses.media.mit.edu/2004spring/mas966/Minsky%201974%20Framework%20for%20knowledge.pdf

// ECS_TAG(ecs, Hyperlink)
// // ECS_TAG(ecs, HyperlinkOut)

// ECS_STRUCT(WikipediaLink,
// {
//     char* wiki_url;
//     zpl array entity pointers (to other url ontology entity hyperlinks)
//     char* content // only in high RAM context, hold content directly in memory...
//     // https://huggingface.co/sentence-transformers/all-MiniLM-L6-v2
//     vector embeddings
//     // multimedia -> this data is too big to hold, but maybe urls to media with natural language description/embedding?
// });

// // Frame vs Terminal

// // Location
// // TODO: Use a flecs module
// ECS_STRUCT(Wikipedia_Location,
// {

// });

ECS_STRUCT(WikipediaPage, {
  char* title;
});

ECS_STRUCT(URL, {
  char* uri;
});