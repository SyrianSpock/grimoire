# Generating slides with pandoc

Very simple to generate slides from markdown.
Start by [installing pandoc](https://pandoc.org/installing.html) and [cloning reveal.js](https://github.com/hakimel/reveal.js/).
Then run

```bash
pandoc -t html5 \
    --standalone \
    --section-divs \
    --template=template-revealjs.html \
    --variable theme="black" \
    --variable transition="linear" \
    --variable revealjs-url="https://revealjs.com" \
    --from markdown-markdown_in_html_blocks+raw_html \
    slides.md -o slides.html
```

You can also set `revealjs-url` to your local clone of reveal.js if you want to display your slides without internet connection.
