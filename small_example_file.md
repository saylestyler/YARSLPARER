An error probably seen before:

```
'xxx does not exist on type CombinedVueInstance<followed by a bunch of stuff>'
```

For a while, in order to silence an this typescript error when developing vue2 component, I just used the `(this as any).theOffendingFunction`

Of course, any `any`s are to be avoided, so here's another way to resolve the issue with legitimate typescript.

Start by importing Vue constructor at top of script file like so:

```ts
// import Vue from 'vue' // old

import _Vue, { VueConstructor } from 'vue' // new
```

Then you can define types, and pass those as _type arguments_ to your now reassigned Vue constructor. So, say you want to invoke a getter GET_ACCOUNT in your component, and when you do so `this.GET_ACCOUNT` you'll get the 'xxx does not exist on [...]'

```ts
export type LocallyPickedGetters = Pick<
  MyGetters, 'GET_ACCOUNT'
>

const Vue = _Vue as VueConstructor<
  _Vue & LocallyPickedGetters
>

export default Vue.extend({
  // proceed as you normally would

  accountInfo() {
    // no error bc now! it certainly exists
    this.GET_ACCOUNT()
  }
})
```
---
title: It Does Indeed Exist on Combined Vue Instance!
date: 2021-12-23
excerpt: a few ways to resolve a confusing TS error for mapped vuex functions
tags:
  - vue2
  - vue
  - typescript
blog: true
