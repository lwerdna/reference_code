function ajax_post(url, query)
{
	var xmlhttp = new XMLHttpRequest();
	console.log("AJAX URL: " + url);
	xmlhttp.open("POST", url, false);
	/* forms have two content types
		- multipart/form-data : the HTTP message body is collection of parts
		  in a MIME blob (like email attachments) so each part has its own
		  'Content-Type' and 'Content-Disposition' and you have to concern
		  yourself with the boundary or divider
		- application/x-www-form-urlencoded : the body of the HTTP message is
		  a (potentially huge) query string of name/value pairs where you have
		  to take care not to collide with '?' '&' and '='
	*/
	xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
	//xmlhttp.setRequestHeader('Content-length', query.length)
	//xmlhttp.setRequestHeader('Connection', 'close')
	xmlhttp.send(query);
	var resp = xmlhttp.responseText;

	if(resp.length > 16)
		console.log("AJAX: " + resp.substr(0, 16) + '...');
	else
		console.log("AJAX: " + resp);

	if(resp.search("A problem occurred in a Python script.") >= 0) {
		document.write(resp);
		console.log("backend error: python script");
	}
	return resp;
}

function ajax_file(url, file_name, file_data)
{
	var query = '';
	query += 'file_name='+encodeURIComponent(file_name);
	query += '&file_data='+encodeURIComponent(file_data);
	return ajax_post(url, query);
}

function upload()
{
	var input_elem = document.getElementById('file');
	var files = input_elem.files;

	if (files.length != 1)
	{
		console.log("ERROR: expected 1 file");
		return;
	}

	var file = files[0];

	var file_name = file.name;

	/* set up a FileReader */
	var reader = new FileReader();
	reader.onload = function(e)
	{
		console.log(file);
		console.log(file.name);
		// e is a "load" object
		// e.target is the FileReader
		ajax_file('cgi-bin/upload.py', file_name, e.target.result)
	}
	reader.onerror = function(e)
	{
		console.log('ERROR: ' + e.type);
	}

	/* execute FileReader */
	reader.readAsArrayBuffer(file)
}
