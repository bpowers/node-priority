{
    "targets": [
        {
            "target_name": "priority",
            "sources": [ "priority.cc" ],
            "include_dirs" : [
 	 			"<!(node -e \"require('nan')\")"
			]
        }
    ],
}