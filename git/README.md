# Git snippets

For the times when you need to invoque git voodoo.

## From submodule to subtree

```bash
./submodule_to_subtree.sh <submodule-path> <submodule-branch>
```

where
- `submodule-path` is the path to the submodule to be merged as subtree
- `submodule-branch` is the branch of the submodule to be merged, defaults to "master"

Read more on why I think git subtree > git submodule on [my blog](https://www.syrianspock.com/software/2018/12/27/submodule-to-subtree-road-to-monorepo/)
