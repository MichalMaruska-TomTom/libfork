### tools to configure the _Fork_ plugin.

A library and a simple tool to load the configuration.

xbased on xlib calls which configure plugins on the pipeline,


## howto use:


    $ forkto -h

read the usage.


    id=$(xinput list --id-only "Virtual core keyboard")
    forkto -k $id < ~/fork.config
