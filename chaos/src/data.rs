use axum::{http::StatusCode, response::IntoResponse, Json};
use serde::{Deserialize, Serialize};

//Assumed we're fine to import. 
use serde_json::{Value, Value::*};

pub async fn process_data(Json(request): Json<DataRequest>) -> impl IntoResponse {
    // Calculate sums and return response
	let (int_sum, string_len) : (Vec<i64>, Vec<usize>) = request.data.iter().filter_map(|val| {
		match val {
			//Extract the generic 'Number' from the Json vals
			Number(json_num) => {
				//Json_Num may be floating, or out-of-scope
				// We ignore floats bc the field is 'int_sum', and accept some ints may be out of range
				json_num.as_i64().map(|s|  (s, 0) )
			},
			String(json_str) => {
				//Return length of string
				Some((0, json_str.as_str().len()))
			},
			//We ignore other types of JSON vals
			_ => None,
		}
	}).unzip();


	//Do we want the len (# bytes) or the number of chars - im going with len for string_len
    let response = DataResponse {
		string_len: string_len.iter().sum(),
		int_sum: int_sum.iter().sum(),
    };

    (StatusCode::OK, Json(response))
}

#[derive(Deserialize)]
pub struct DataRequest {
    // Add any fields here
	data:  Vec<Value>,
}

#[derive(Serialize)]
pub struct DataResponse {
    // Add any fields here
	string_len: usize,
	int_sum: i64,
}
